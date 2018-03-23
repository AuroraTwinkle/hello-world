#!/usr/bin/env python3
# -*- coding:utf-8 -*-

__author__ = 'Aurora-Twinkle'

def f():
    x=-1459685
    s=(x>0)-(x<0)
    r=int(str(s*x)[::-1])
    print(r)

f()