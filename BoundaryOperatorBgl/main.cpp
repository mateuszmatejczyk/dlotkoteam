#include "BoundaryOperatorFactoryBgl.h"

int main(){
	BoundaryOperatorFactory b;
	b.readFromFile("graph");
	BoundaryOperator op = b.getBoundary();
	b.writeToFile( (string)"result" , op );
	//cout<<op.get( 0, 5 )<<endl;
	//cout<<op.get( 0, 1 )<<endl;
	//cout<<op.get( 2 , 30 )<<endl;
}
