
from curses import wrapper


def mywrapper(fc):
    def internalfunc():
        print("internal func!")
        fc()
    return internalfunc

@mywrapper
def func():
    print("hello")

func()


def mywrapper2(fc):
    def internalfunc(*argc,**argv):
        print("internal!!")
        fc(*argc,**argv)
    return internalfunc

@mywrapper2
def func2(t1,t2):
    print("func2{},seconed {}".format(t1,t2))

func2('this first','this seconed')