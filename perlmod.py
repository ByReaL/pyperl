# Copyright 2001 ActiveState

"""perlmod - Simplified access to Perl modules

This module provide adaptors that makes it easier to access and use
Perl modules from Python.  It provide classes to encapsulate Perl
modules and Perl classes.

Example usage of an Perl OO module:

   from perlmod import Perl
   HTTP = Perl.HTTP

   ua = Perl.LWP.UserAgent()
   res = ua.request(HTTP.Request("GET", "http://www.python.org"))
   if res.is_success():
       print res.content()
   else:
       print res.status_line()

Another way to do it:

   from perlmod import PerlClass

   # Import classes
   LWP_UserAgent = PerlClass("LWP::UserAgent")
   HTTP_Request  = PerlClass("HTTP::Request")

   # do the stuff
   ua = LWP_UserAgent()
   res = ua.request(HTTP_Request("GET", "http://www.python.org"))
   if res.is_success():
       print res.content()
   else:
       print res.status_line()

An attribute prefixed with '__' is regarded as a class methods:

   from perlmod import Perl
   u = Perl.URI.file.__cwd()  # $u = URI::file->cwd;
   print u

Example usage of an functional style module:

   from perlmod import PerlModule
   print PerlModule("MIME::Base64").encode("foo")

Explicit manual import:

   from perlmod import PerlModule
   encode_base64 = PerlModule("MIME::Base64").encode

   print encode_base64("foo")

Import all functions that are exported by default (@EXPORT):

   from perlmod import PerlModule
   PerlModule("MIME::Base64").__import__("*", locals())   

   print encode_base64("foo")
"""

class PerlClass:
    def __init__(self, name = None, module=None, ctor="new"):
        self.name = name
        self.module = module or name
        self.ctor = ctor
        
    def __getattr__(self, name):
        if name[:2] == '__':
            if name[-2:] != '__' and name != '__':
                return PerlClass(self.name, ctor=name[2:])
            raise AttributeError(name)
        if self.name:
            name = self.name + "::" + name
        return PerlClass(name)

    def __call__(self, *args):
        import perl
        name = self.name
        perl_require(self.module)
        return perl.callm(*(self.ctor, name) + args)

class PerlModule:
    def __init__(self, name, __wantarray__ = 0):
        self.name = name
        self.wantarray = __wantarray__

    def __getattr__(self, name):
        if name[:2] == '__':
                raise AttributeError(name)
        perl_require(self.name)
        wantarray = self.wantarray
        if len(name) > 6 and name[-6:] == '_tuple':
            name = name[:-6]
            wantarray = 1
        full_name = self.name + "::" + name
        import perl
        func = perl.get_ref(full_name)
        func.__wantarray__ = wantarray
        return func

    def __import__(self, funcs, namespace):
        perl_require(self.name)
        import perl
        if funcs == '*':
            funcs = tuple(perl.get_ref("@" + self.name + "::EXPORT"))
        elif type(funcs) == type(""):
            funcs = (funcs,)
        for f in funcs:
            namespace[f] = perl.get_ref(self.name + "::" + f)

Perl = PerlClass()


# Loading of perl modules

INC = {}

try:
    from thread import get_ident
except ImportError:
    def get_ident():
        return 1

def perl_require(mod):
    # Some caching since the real 'perl.require' is a bit
    # heavy.
    id = get_ident()
    global INC
    try:
        return INC[id][mod]
    except KeyError:
        pass
    
    import perl
    if id not in INC:
        INC[id] = {}
    INC[id][mod] = perl.require(mod)
    return INC[id][mod]
