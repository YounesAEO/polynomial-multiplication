from ctypes import *

class Poly(Structure):
    _fields_= [
        ("coeff", POINTER(c_int)),
        ("degree", c_int)
    ]

_lib = cdll.LoadLibrary("D:\IMA\MODEL\projet\kara\poly.so")

"""generate function"""
generate = _lib.generate
generate.argtypes = [c_int]
generate.restype = POINTER(Poly)

"""degree max function"""
degree_max = _lib.degree_max
degree_max.argtypes = [POINTER(Poly)]

"""Mod function"""
mod = _lib.mod
mod.argtypes = [Poly, c_int]
mod.restype = Poly

"""karatsuba function"""
karatsuba = _lib.karatsuba
karatsuba.argtypes = [Poly, Poly]
karatsuba.restype = Poly

"""Toom cook function"""
toomcook = _lib.toomcook
toomcook.argtypes = [Poly, Poly, c_int]
toomcook.restype = Poly

"""Naive multiplication"""
mult = _lib.mult
mult.argtypes = [Poly, Poly, c_int]
mult.restype = Poly