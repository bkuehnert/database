#include "Relation.h"

void whatGrade(char* studentname, char* coursename, Relation* snap, Relation* csg)
{
	int columns[] = {1,1,0,0};
	Relation* newRel = project(snap, columns);
	Relation* joined = joinRelation(newRel, csg, 0, 1);
	print(rel_query(joined, createTuple(4, "*", studentname, coursename, "*")));
}
