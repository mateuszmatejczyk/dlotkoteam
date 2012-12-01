
#include "GraphCreatorBgl.h"

int main() {
	SympleksToGraphConvereter stgc;
	stgc.readFromFile("/home/maciek/Informatyka/Programy/dane/poincare.dat");
	stgc.writeGraphToFileVertexNode("/home/maciek/Informatyka/Programy/dane/graphPoincare.txt");
	list<int> temp; temp.push_back(1); temp.push_back(2); temp.push_back(4); temp.push_back(9);
	stgc.getBoundry(temp);
	//stgc.readFromFile("E:\\Dropbox\\Studia\\Informatyka\\ProjektZespolowy\\dane\\poincare.dat");
	//stgc.writeGraphToFileStandard("E:\\Dropbox\\Studia\\Informatyka\\ProjektZespolowy\\dane\\graphPoincare.dat");
	stgc.staticistics();
	stgc.writeLegend("legend.txt");
	stgc.writeGraphToFileStandard("testing.txt");
	stgc.writeAllVerticesToFile("vertixes.txt");
	//stgc.writeLegend("E:\\Dropbox\\Studia\\Informatyka\\ProjektZespolowy\\dane\\legendPoincare.dat");

	return 0;
}
