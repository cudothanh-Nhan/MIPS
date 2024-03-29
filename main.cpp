#include "instruction.h"

using namespace std;

Instruction* navigationCommand(string _instruction){
    string name = getWord(_instruction, 1);
    if(!name.compare("add") || (!name.compare("addu"))) return new Add;
    else if (!name.compare("abs")) return new Absolute;
    else if(!name.compare("sub") || (!name.compare("subu"))) return new Subtract;
    else if(!name.compare("and")) return new And;
    else if(!name.compare("not")) return new Not;
    else if(!name.compare("or")) return new Or;
    else if(!name.compare("xor")) return new Xor;
    else if(!name.compare("sll")) return new Sll;
    else if(!name.compare("srl")) return new Srl;
    else if(!name.compare("sra")) return new Sra;
    else if(!name.compare("mult")) return new Mult;
    else if(!name.compare("div")) return new Div;
    else if(!name.compare("jr")) return new Jr;
    else if(!name.compare("mfhi")) return new Mfhi;
    else if(!name.compare("mflo")) return new Mflo;
    else if(!name.compare("sltu")) return new Sltu;
    else if(!name.compare("slt")) return new Sltu;
    else if(!name.compare("mtc1")) return new Mtc1;
    else if(!name.compare("mfc1")) return new Mfc1;
    else if(!name.compare("move")) return new Move;
    else if(!name.compare("mov.s")) return new MoveS;
    else if(!name.compare("addi") || !name.compare("addiu")) return new Addi;
    else if(!name.compare("subi")) return new Subi;
    else if(!name.compare("andi")) return new Andi;
    else if(!name.compare("ori")) return new Ori;
	else if(!name.compare("slti")) return new Slti;	
	else if(!name.compare("li")) return new Li;
    else if(!name.compare("beq")) return new Beq;
    else if(!name.compare("bne")) return new Bne;
    else if(!name.compare("bgez")) return new Bgez;
    else if(!name.compare("beqz")) return new Beqz;
    else if(!name.compare("bgt")) return new Bgt;
    else if(!name.compare("bge")) return new Bge;
    else if(!name.compare("blt")) return new Blt;
    else if(!name.compare("ble")) return new Ble;
    else if(!name.compare("la")) return new La;
    else if(!name.compare("lw")) return new Lw;
    else if(!name.compare("sw")) return new Sw;
    else if(!name.compare("lh")) return new Lh;
    else if(!name.compare("sh")) return new Sh;
    else if(!name.compare("lb")) return new Lb;
    else if(!name.compare("sb")) return new Sb;
    else if(!name.compare("swc1")) return new Swc1;
    else if(!name.compare("lwc1")) return new Lwc1;
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
    cmd.write("$sp", reg.getRegisterValue("$sp"));
    cop.init();
}

// Replace int main() with int process()
int main(int argc, char* argv[]){
    // START HERE
    fileIn.loadLink("testAssembly.txt");
    setup();
    while(fileIn.getInstruction(reg.getRegisterValue("pc")).compare("")) {
        string instruction = fileIn.getInstruction(reg.getRegisterValue("pc"));

        cout << "------------------------------------------------------" <<'\n';
        cout << "Next Command: " << optimizeString(instruction) << '\n';
        cout << "------------------------------------------------------" << '\n';
        //cmd.pause();
        Instruction* ptr = navigationCommand(instruction);
        if(ptr != nullptr) {
            ptr->init(instruction);
            ptr->execute();
        }
        reg.setRegisterValue("pc", reg.getRegisterValue("pc") + 4);
        if(fileIn.getInstruction(reg.getRegisterValue("pc")).compare("")) {
            cmd.write("pc", reg.getRegisterValue("pc"));
        }

        if(isExit == 1) break;
        //cmd.print();
        cout << sys.consoleField << '\n';
        delete ptr;
    }

    // int a;
    // cin >> a;
    // cout << fileIn.getLabelAddress("SAME_SIGN") << '\n';
    // cout << fileIn.getInstruction(a) << '\n';
    cout << "------------------------------------------------------" << '\n';
    cout << "PROGRAM HAS ENDED!!" << '\n';
    cout << "------------------------------------------------------" << '\n';
    return 0;
}