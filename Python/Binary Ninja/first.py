from binaryninja.plugin import BackgroundTaskThread,PluginCommand

class Solver(BackgroundTaskThread):
    # bv是binaryview对象
    def __init__(self, bv):
        BackgroundTaskThread.__init__(self, "Resolving...", True)
        self.bv = bv

    def run(self):
        print('hello')

def solve(bv):
    s = Solver(bv)
    s.start()

PluginCommand.register("Test", "this is description", solve)
