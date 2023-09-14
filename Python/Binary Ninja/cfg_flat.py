#
#Backspace



from binaryninja import *

class fsm:
    def __init__(self) -> None:
        pass
        
    def is_dispatch_bb(self,bb:BasicBlock):
    # 模式匹配分发块
        instruction_count=0
        for tuple_insn in bb:
            for tokens in tuple_insn[0]:
                # 打印一个个TextToken
                pass
                #print(tokens)
            #print('指令大小 '+str(tuple_insn[1]))
            instruction_count = instruction_count+1
        if instruction_count == 2:
            return True
        
        # --
        return False    
    
    def start(self):
        print('-- 当前分析的函数 '+hex(current_function.start))
        for bb in current_function.basic_blocks:
            if self.is_dispatch_bb(bb):
                self.dispatch_bb_list.append(bb)

        # 从分发块中提取出State和Action

        
    def log(self):
        for dispatch_bb in self.dispatch_bb_list:
            print(hex(dispatch_bb.start))
        
    dispatch_bb_list:list=[]



m=fsm()
m.start()
        
m.log()

