# This file is distributed under the terms of the GNU General Public license.
# Copyright (C) 1999 Aloril (See the file COPYING for details).

import importlib
import types

from common import log


# \defgroup PythonGoals Goal Classes
# \brief Base class for all goals
# \ingroup PythonGoals
class Goal:
    def __init__(self, desc="some goal", fulfilled=None, subgoals=None,
                 validity=None, time=None, debug=0):
        """ Init
            Args:
                desc (string): A user facing description of the goal
                fulfilled (func): A function returning a bool whether the goal is fulfilled or not.
                    Fulfilled goals will be skipped by the mind code when determining which goal to run next.
                subgoals (list): A list of subgoals which will be checked and executed in order.
                validity (func): A function returning bool whether the goal still is valid. Used mainly by other goals.
                time (object): An optional time object. If set, the goal is only valid if the time has passed.
                debug (int): A flag declaring whether debug output should be enabled.
        """
        if subgoals is None:
            subgoals = []
        self.desc = desc
        # mind sets these:
        # self.key
        if fulfilled:
            self.fulfilled = fulfilled
        else:
            self.fulfilled = lambda me: False

        # If no validity function is supplied the goal is always considered valid
        if validity:
            self.validity = validity
        else:
            self.validity = lambda me: True

        # filter out any None subgoals
        self.subgoals = [item for item in subgoals if item is not None]
        self.time = time
        self.debug = debug
        self.vars = []
        # keeps track of whether the goal is fulfilled or not
        # this is mainly of use for inspection and diagnosis
        self.is_fulfilled = False
        # any subgoal/function/method can set this and
        # it's checked at start of check_goal_rec
        # and NPCMind.py fulfill_goals uses it too to remove goals from list
        self.irrelevant = False
        # Tracks the number of errors this goal (or any of its subgoals) has produced.
        # This is used by NPC code to remove troublesome goals from the processing
        self.errors = 0
        # If an error has occurred, the description of the last one is stored here.
        # This is mainly of use for debugging.
        self.lastError = ""

        self.lastProcessedGoals = None

    def __repr__(self):
        return self.info()

    def __str__(self):
        return self.info()

    def triggering_goals(self):
        goals = []
        for sub_goal in self.subgoals:
            if hasattr(sub_goal, "triggering_goals"):
                goals.extend(sub_goal.triggering_goals())
        return goals

    def info(self):
        name = self.__class__.__name__
        if name == "Goal":
            return name + "(" + repr(self.desc) + ")"
        var = ""
        for v in self.vars:
            if var:
                var = var + ","
            var = var + repr(getattr(self, v))
        return name + "(" + var + ")"

    def is_valid(self, me):
        """Checks if this goal is valid. By this we mean whether the goal is possible to fulfill. 
        If no validity function was supplied at goal creation time the goal is always considered valid. """
        return self.validity(me)

    def check_goal(self, me, time):
        """executes goal. Any response that's not None causes the goal checking code to stop after this goal"""
        if self.debug:
            log.thinking("GOAL desc: " + str(self))
        res, debug_info = self.check_goal_rec(me, time, 0, "")
        if len(debug_info) != 0:
            # Keep a copy of the debug info for the "report" method.
            self.lastProcessedGoals = debug_info
        return res

    def check_goal_rec(self, me, time, depth, debug_info):
        """check (sub)goal recursively. 
        
        This is done by iterating over all sub goals, breaking if any sub goal returns an operation."""
        res = None
        if self.irrelevant:
            return res, debug_info
        # is it right time range?
        if self.time and not time.is_now(self.time):
            return res, debug_info
        if self.debug:
            log.thinking("\t" * depth + "GOAL: bef fulfilled: " + self.desc + " " + repr(self.fulfilled))
        if self.fulfilled(me):
            self.is_fulfilled = 1
            if self.debug:
                log.thinking("\t" * depth + "GOAL: is fulfilled: " + self.desc + " " + repr(self.fulfilled))
            return res, debug_info
        else:
            if self.debug:
                log.thinking("\t" * depth + "GOAL: is not fulfilled: " + self.desc + " " + repr(self.fulfilled))
            self.is_fulfilled = 0
        debug_info = debug_info + "." + self.info()
        # Iterate over all sub goals, but break if any goal returns an operation
        for sg in self.subgoals:
            if sg is None:
                continue
            if isinstance(sg, types.FunctionType) or isinstance(sg, types.MethodType):
                if self.debug:
                    log.thinking("\t" * depth + "GOAL: bef function: " + repr(sg) + " " + repr(res))
                res = sg(me)
                if self.debug:
                    log.thinking("\t" * depth + "GOAL: aft function: " + repr(sg) + " " + repr(res))
                debug_info = debug_info + "." + sg.__name__ + "()"
                if res is not None:
                    # If the function generated an op, stop iterating here and return
                    return res, debug_info
            else:
                if self.debug:
                    log.thinking("\t" * depth + "GOAL: bef sg: " + sg.desc)
                # If the subgoal is irrelevant, remove it
                if sg.irrelevant:
                    self.subgoals.remove(sg)
                    continue
                res, debug_info = sg.check_goal_rec(me, time, depth + 1, debug_info)
                if self.debug:
                    log.thinking("\t" * depth + "GOAL: aft sg: " + sg.desc + ", Result: " + str(res))
                # If the subgoal generated an op, stop iterating here and return
                if res is not None:
                    return res, debug_info
        return res, debug_info

    def report(self):
        """provides extended information about the goal,
        as well as all subgoals"""
        name = self.__class__.__name__
        report = {"name": name, "description": self.desc, "fulfilled": self.is_fulfilled}
        if self.lastProcessedGoals:
            report["lastProcessedGoals"] = self.lastProcessedGoals

        subgoals = []
        for sg in self.subgoals:
            if not isinstance(sg, types.FunctionType) and not isinstance(sg, types.MethodType) and sg is not None:
                subgoals.append(sg.report())
        if len(subgoals) > 0:
            report["subgoals"] = subgoals

        if len(self.vars) > 0:
            variables = {}
            for v in self.vars:
                variables[v] = str(getattr(self, v))
            report["variables"] = variables

        if self.errors > 0:
            report["errors"] = self.errors
            report["lastError"] = self.lastError
        return report


def goal_create(goal_element):
    if goal_element is None:
        return None

    if hasattr(goal_element, 'class'):
        goal_class = goal_element['class']
        splits = goal_class.split('.')
        module_name = '.'.join(splits[0:-1])
        class_name = splits[-1]

        module = importlib.import_module(module_name)
        class_ = getattr(module, class_name)
        params = {}
        if hasattr(goal_element, 'params'):
            params = goal_element['params']

        print('Creating an instance of {}'.format(goal_class))
        try:
            instance = class_(**params)

            if instance:
                return instance
            else:
                print('Could not create goal from data\n {}'.format(str(goal_element)))
        except Exception:
            print('Error when creating goal from data\n {}'.format(str(goal_element)))
            raise
    return None
