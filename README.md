// (C) Copyright 2013, Tianlin Shi (tianlin [at] mit [dot] edu)
// The code implements paper : A Fully Polynomial-Time Approximation Scheme for Approximating a Sum of Random Variables
//                                                 [J. Li, T. Shi, 2013] http://arxiv.org/abs/1303.6071.


// SORV is free software; you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or (at your
// option) any later version.

// SORV is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
// for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA

Build & Install:
python setup.py build
sudo python setup.py install

Usage:
in python: import sorvlib
the algorithm relies on oracle calls to probability distributions. in python, define functions like

def uniform_dist1(s1, s2):
    n = 10
    res = 0
    if(min(s2,n-1) < max(s1, 0)):
        return 0
    return (min(s2,n-1)-max(s1,0)+1)*1.0/n

sorvlib.computeSorv takes three args: func_list, C, epsilon.

func_list is a list all function instances.
for example, use: sorvlib.computeSorv([uniform_dist1 uniform_dist1], 3, 0.1) 
to compute 1 \pm 0.1 approximation of the probability such that the sum of two uniform distributed variables is no larger than 3.



