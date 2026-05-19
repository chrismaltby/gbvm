#!/usr/bin/env python
# -*- coding: utf-8 -*-
# vim: sts=4 sw=4 et
# Description: Unit test checker
# Author: Tony Pavlov (untoxa)
# SPDX-License-Identifier: MIT

import os
import sys
import json
import difflib
import pprint
from array import array
from PIL import Image, ImageChops

from BGB_toolkit import load_noi, read_bgb_snspshot

no_color = os.getenv("NO_COLOR") is not None

red = lambda text: text if no_color else f"\033[31m{text}\033[0m"
green = lambda text: text if no_color else f"\033[32m{text}\033[0m"
white = lambda text: text if no_color else f"\033[38;2;255;255;255m{text}\033[0m"

def get_rule_desc(config_file):
    desc = config.get('description', '')
    if len(desc) > 0:
        return '{:s} ({:s})'.format(config_file, desc)
    else:
        return config_file

def CHECKSCREEN(file_name):
    image_one = Image.open(file_name).convert('RGB')
    image_two = Image.open(sys.argv[4]).convert('RGB')

    diff = ImageChops.difference(image_one, image_two)

    return (diff.getbbox() is None)


def exec_rule(rule):
    global rule_result
    rule_result = False
    exec('global rule_result; rule_result = {:s}'.format(rule))
    return rule_result

mem_map = { 'WRAM': 0xC000, 'VRAM': 0x8000, 'OAM': 0xFE00, 'HRAM': 0xFF80 }
def ADDR(symbol, base):
    if type(base) is str:
        base = mem_map[base.upper()]
    return symbols.get(symbol) - base

def DATA(section, address, len = 0):
    if len > 1:
        return snapshot[section][address:address + len]
    else:
        return snapshot[section][address]

def ASCIIZ(section, address):
    ofs = address
    data = snapshot[section]
    fin = ofs
    while data[fin] != 0: fin += 1
    return str(data[ofs:fin], 'ascii') if fin - ofs > 0 else ''

def ASSERT_EQ(a, b):
    if a != b:
        diff = get_diff(a, b)
        sys.stdout.write(
            "\nAssertion failed:\n\n{:s}\n{:s}\n\n{:s}\n\n".format(
                green("- Expected"), red("+ Received"), diff
            )
        )
    return a == b

def ASSERT_NE(a, b):
    if a == b:
        diff = get_diff(a, b)
        sys.stdout.write(
            "\nAssertion failed:\n\n{:s}\n{:s}\n\n{:s}\n\n".format(
                green("- Expected values to differ"),
                red("+ Received equal values"),
                diff
            )
        )
    return a != b

def get_diff(a, b):
    a_str = pprint.pformat(a) 
    b_str = pprint.pformat(b)    
    result = ""
    codes = difflib.SequenceMatcher(a=a_str, b=b_str).get_opcodes()
    for code in codes:
        if code[0] == "equal": 
            result += white(a_str[code[1]:code[2]])
        elif code[0] == "delete":
            result += red(a_str[code[1]:code[2]])
        elif code[0] == "insert":
            result += green(b_str[code[3]:code[4]])
        elif code[0] == "replace":
            result += (red(a_str[code[1]:code[2]]) + green(b_str[code[3]:code[4]]))
    return result

def handle_failure(rule, message=""):
    error_message = f'{red("✕")} TEST: {get_rule_desc(sys.argv[1])} FAILED!\n    FAILED RULE: "{rule}"'
    if message:
        error_message += f"\n    {message}"
    sys.exit(error_message)

if len(sys.argv) == 1:
    sys.exit(('Unit test checker v0.1\n'
              '  USAGE: unit_checker.py <rules.json> <symbols.noi> <snapshot.sna> <screenshot.bmp>'))

config = {}

with open(sys.argv[1]) as json_file:
    config = json.load(json_file)

symbols = load_noi(sys.argv[2])
symbols = {value:key for key, value in symbols.items()}

snapshot = read_bgb_snspshot(sys.argv[3])

rules = config.get('rules', [])

for rule in rules:
    if isinstance(rule, (list, tuple)):
        if not exec_rule(rule[0]):
            handle_failure(rule[0], rule[1])
    else:
        if not exec_rule(rule):
            handle_failure(rule)

sys.stdout.write('TEST: {:s} PASSED\n'.format(get_rule_desc(sys.argv[1])))
