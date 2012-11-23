#include "GraphCreator.h"
using namespace std;

int main() {
	SympleksToGraphConvereter stgc;
	stgc.readFromFile("/home/maciek/Informatyka/Programy/dane/poincare.dat");
	stgc.writeGraphToFileVertexNode("/home/maciek/Informatyka/Programy/dane/graphPoincare.txt");
	//stgc.readFromFile("E:\\Dropbox\\Studia\\Informatyka\\ProjektZespolowy\\dane\\poincare.dat");
	//stgc.writeGraphToFileStandard("E:\\Dropbox\\Studia\\Informatyka\\ProjektZespolowy\\dane\\graphPoincare.dat");
	stgc.staticistics();
	//stgc.writeLegend("E:\\Dropbox\\Studia\\Informatyka\\ProjektZespolowy\\dane\\legendPoincare.dat");


	return 0;
}
