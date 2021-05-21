from distutils.core import setup, Extension
spam_mod = Extension('spam',sources=['spam.c'])
setup(name="spam",
		version="1.0",
		description="A sample extension module",
		ext_modules=[spam_mod])


