from distutils.core import setup, Extension
import os

os.environ["CC"] = "g++-4.8 -std=c++11 -O3" 
os.environ["CXX"] = "g++-4.8 -std=c++11 -O3"

module = Extension('sorvlib',
                    include_dirs = ['/usr/local/include', '/usr/local/include/sphinxbase', '/usr/local/include/pocketsphinx'],
                    libraries = [],
                    library_dirs = ['/usr/local/lib/', '/usr/local/Cellar/portaudio/19.20111121/lib'],
                    sources = ['sorv.cpp', 'sorv_python.cpp'])

setup (name = 'SorvLib',
       version = '1.0',
       description = 'Compute the distribution of a sum of random variables within polynomial time.',
       author = 'Tianlin Shi',
       author_email = 'tianlin@mit.edu',
       url = '',
       long_description = '',
       ext_modules = [module])

