#include "instruction.h"

using namespace std;

Instruction* navigationCommand(string _instruction){
    string name = getWord(_instruction, 1);
    if(!name.compare("add")) return new Add;
    else if(!name.compare("subtract")) return new Subtract;
    else if(!name.compare("and")) return new And;
    else if(!name.compare("sll")) return new Sll;
    else if(!name.compare("mult")) return new Mult;
    else if(!name.compare("div")) return new Div;
    else if(!name.compare("jr")) return new Jr;
    else if(!name.compare("mfhi")) return new Mfhi;
    else if(!name.compare("mflo")) return new Mflo;
    else if(!name.compare("sltu")) return new Sltu;
    else if(!name.compare("addi")) return new Addi;
    else if(!name.compare("andi")) return new Andi;
    else if(!name.compare("ori")) return new Ori;
	else if(!name.compare("slti")) return new Slti;	
	else if(!name.compare("li")) return new Li;
    else if(!name.compare("beq")) return new Beq;
    else if(!name.compare("bne")) return new Bne;
    else if(!name.compare("la")) return new La;
    else if(!name.compare("lw")) return new Lw;
    else if(!name.compare("sw")) return new Sw;
    else if(!name.compare("lh")) return new Lh;
    else if(!name.compare("sh")) return new Sh;
    else if(!name.compare("lb")) return new Lb;
    else if(!name.compare("sb")) return new Sb;
    else if(!name.compare("j")) return new Jump;
    else if(!name.compare("jal")) return new Jal;
    else if(!name.compare("syscall")) {
        sys.execute();
        return nullptr;
    }
    else return nullptr;
}
void setup() {
    cmd.print();
    reg.init();
}

// Replace int main() with int process()
int main(){
    setup();
<<<<<<< HEAD
=======
    //FileAssembly fileIn("testAssembly.txt");
>>>>>>> 106380e78a6190bbf7188507f846ff85cb684cfe
    while(fileIn.getInstruction(reg.getRegisterValue("pc")).compare("")) {
        string instruction = fileIn.getInstruction(reg.getRegisterValue("pc"));
        Instruction* ptr = navigationCommand(instruction);
        cout << "------------------------------------------------------" <<'\n';
        cout << "Next Command: " << optimizeString(instruction) << '\n';
        cout << "------------------------------------------------------" << '\n';

        if(ptr != nullptr) {
            ptr->init(instruction);
            ptr->execute();
        }
        reg.setRegisterValue("pc", reg.getRegisterValue("pc") + 4);
        if(fileIn.getInstruction(reg.getRegisterValue("pc")).compare("")) {
            cmd.write("pc", reg.getRegisterValue("pc"));
        }
        cmd.pause();
        if(isExit == 1) break;
        cmd.print();
        cout << sys.consoleField << '\n';
    }    
    cout << "------------------------------------------------------" << '\n';
    cout << "PROGRAM HAS ENDED!!" << '\n';
    cout << "------------------------------------------------------" << '\n';
    return 0;
}
