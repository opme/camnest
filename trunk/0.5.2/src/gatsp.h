#ifndef GATSP_H
#define GATSP_H
#include <QtGui>
#include <QWidget>
#include "qpointfwithparent.h"
/** we have to start with a random population .
CrossOver with  Sushil J. Louis greedy crossOver
Mutate randomly by swapping 2 (or more cities positions)
Select the elite parents that will generate the new offsprings with Roulette Wheel Selection

**/
void swapVals(QPFWPVector &vect,int pos1,int pos2) ;


class Chromosome
{
public:
	 Chromosome();
	 QPFWPVector elements;
	 QPFWPVector createNew(QPFWPVector points);
	 int MySize;
	 virtual ~Chromosome();
	 double routeLength;
	 double fitness;
	 void setElements(QPFWPVector points,bool random);
	 void setFitness(double fit){this->fitness=fit;}
	 void setRoutelength();
};




class Popu
{
public:
	 
	 Popu();
	 void computeTotalRoute();
	 void sortContent();
	 void createNewGen();
	 QPFWPVector init(QPFWPVector points);
	 void selectParents(Chromosome* parent1,Chromosome* parent2,int posd);
	 Chromosome cross(Chromosome parent1, Chromosome parent2);
	 void mutateImprove(int pos);
	 void mutate(int i);
	 
	 QVector <Chromosome > newGen;
	 QVector <Chromosome > content;
	 double totalRoute;
	 int popSize,Max_iter,chromoSize;

};


class Population
{
public:
	 
	 Population(QPFWPVector points);
	 virtual ~Population();
	 QVector <Chromosome *> content;
	 double totalRoute;
	 int popSize;
	 void selectElite();
	 void mutate(Chromosome *offspring);
	  Chromosome *crossoverSimple(Chromosome *parent1, Chromosome *parent2);
	 Chromosome *crossover(Chromosome *parent1, Chromosome *parent2);
};

 class GAThread : public QThread
 {
     Q_OBJECT

 protected:
     void run();
 };

 
#endif // GATSP_H
