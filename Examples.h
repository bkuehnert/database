#include "Relation.h"

void whatGrade(char* studentname, char* coursename, Relation* snap, Relation* csg)
{
	int columns[] = {1,1,0,0};
	int columns2[] = {0,0,0,1};
	Relation* result = project(selection(selection(joinRelation(project(snap, columns), csg, 0, 1),0,1,studentname),0,2,coursename),columns2);
	print(rel_query(result, createTuple(1,"*")));
}

void whereIs(char* studentname, char* time, char* day, Relation* cdh, Relation* snap, Relation* csg, Relation* cr)
{
	int columns1[] = {1,0,0,0};
	int columns2[] = {1,0,0};
	int columns3[] = {1,0,0};
	int columns4[] = {0,1};

	Relation* result = project(joinRelation(joinRelation(project(joinRelation(csg, project(selection(snap, 0, 1, studentname),columns1),1,0),columns2),project(selection(selection(cdh, 0,1,day),0,2,time),columns3),0,0),cr,0,0),columns4);

	print(rel_query(result, createTuple(1,"*")));
}
