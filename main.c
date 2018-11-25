#include "Relation.h"
#include "Examples.h"

int main()
{
	//Create CSG
	int csg_hash[] = {1,0,0};
	char* csg_names[] = {"Course", "Student", "Grade"};
	Relation* csg = create_Relation(3, 1, csg_hash, csg_names);
	
	char* csg_t1[] = {"CS101", "12345", "A"};
	char* csg_t2[] = {"CS101", "67890", "B"};
	char* csg_t3[] = {"EE200", "12345", "C"};
	char* csg_t4[] = {"EE200", "22222", "B+"};
	char* csg_t5[] = {"CS101", "33333", "A-"};
	char* csg_t6[] = {"PH100", "67890", "C+"};

	rel_insert(csg, create_Tuple(3,csg_t1));
	rel_insert(csg, create_Tuple(3,csg_t2));
	rel_insert(csg, create_Tuple(3,csg_t3));
	rel_insert(csg, create_Tuple(3,csg_t4));
	rel_insert(csg, create_Tuple(3,csg_t5));
	rel_insert(csg, create_Tuple(3,csg_t6));

	//Create SNAP
	int snap_hash[] = {0,1,0,0};
	char* snap_names[] = {"Student", "Number", "Address", "Phone"};
	
	Relation* snap = create_Relation(4, 0, snap_hash, snap_names);
	char* snap_t1[] = {"12345", "C. Brown", "12 Apple St.", "555-1234"};
	char* snap_t2[] = {"67890", "L. Van Pelt", "34 Pear Ave.", "555-5678"};
	char* snap_t3[] = {"22222", "P. Patty", "56 Grape Blvd.", "555-9999"};

	rel_insert(snap, create_Tuple(4, snap_t1));
	rel_insert(snap, create_Tuple(4, snap_t2));
	rel_insert(snap, create_Tuple(4, snap_t3));

	//Create CP
	int cp_hash[] = {0,0};
	char* cp_names[] = {"Course", "Prerequisite"};

	Relation* cp = create_Relation(2, 0, cp_hash, cp_names);
	char* cp_t1[] = {"CS101", "CS100"};
	char* cp_t2[] = {"EE200", "EE005"};
	char* cp_t3[] = {"EE200", "CS100"};
	char* cp_t4[] = {"CS120", "CS101"};
	char* cp_t5[] = {"CS121", "CS120"};
	char* cp_t6[] = {"CS205", "CS101"};
	char* cp_t7[] = {"CS206", "CS121"};
	char* cp_t8[] = {"CS206", "CS205"};

	rel_insert(cp, create_Tuple(2, cp_t1));
	rel_insert(cp, create_Tuple(2, cp_t2));
	rel_insert(cp, create_Tuple(2, cp_t3));
	rel_insert(cp, create_Tuple(2, cp_t4));
	rel_insert(cp, create_Tuple(2, cp_t5));
	rel_insert(cp, create_Tuple(2, cp_t6));
	rel_insert(cp, create_Tuple(2, cp_t7));
	rel_insert(cp, create_Tuple(2, cp_t8));

	//Create CDH
	int cdh_hash[] = {0,1,0};
	char* cdh_names[] = {"Course", "Day", "Hour"};

	Relation* cdh = create_Relation(3, 0, cdh_hash, cdh_names);

	char* cdh_t1[] = {"CS101", "M", "9AM"};
	char* cdh_t2[] = {"CS101", "W", "9AM"};
	char* cdh_t3[] = {"CS101", "F", "9AM"};
	char* cdh_t4[] = {"EE200", "Tu", "10AM"};
	char* cdh_t5[] = {"EE200", "W", "10AM"};
	char* cdh_t6[] = {"EE200", "Th", "10AM"};

	rel_insert(cdh, create_Tuple(3, cdh_t1));
	rel_insert(cdh, create_Tuple(3, cdh_t2));
	rel_insert(cdh, create_Tuple(3, cdh_t3));
	rel_insert(cdh, create_Tuple(3, cdh_t4));
	rel_insert(cdh, create_Tuple(3, cdh_t5));
	rel_insert(cdh, create_Tuple(3, cdh_t6));

	//Create CR
	int cr_hash[] = {0,1};
	char* cr_names[] = {"Course", "Room"};

	Relation* cr = create_Relation(2, 0, cr_hash, cr_names);

	char* cr_t1[] = {"CS101", "Turing Aud."};
	char* cr_t2[] = {"EE200", "25 Ohm Hall"};
	char* cr_t3[] = {"PH100", "Newton Lab."};

	rel_insert(cr, create_Tuple(2, cr_t1));
	rel_insert(cr, create_Tuple(2, cr_t2));
	rel_insert(cr, create_Tuple(2, cr_t3));


	printRel(csg);
	printRel(snap);
	printRel(cp);
	printRel(cdh);
	printRel(cr);

	printf("Executing lookup((\"CS101\",\"12345\",\"*\"), CSG):\n");
	print(rel_query(csg, createTuple(3, "CS101", "12345", "*")));

	//printf("\nExecuting lookup((\"CS205\",\"CS120\"), CP):\n");
	//print(rel_query(cp, createTuple(2, "CS101", "*")));
	
	printf("\n\n\nExecuting delete((\"CS101\",*), CR)\n");
	printf("First, the Course-Room table before:\n");
	printRel(cr);
	rel_delete(cr, createTuple(2, "CS101", "*"));
	printf("Now, the Course-Room table after:\n");
	printRel(cr);

	printf("\nExectuing insert((\"CS205\",\"CS120\"),CP)\n");
	printf("First, the Course-Prerequisite table before:\n");
	printRel(cp);
	rel_insert(cp, createTuple(2, "CS205", "CS120"));
	printf("Now, the Course-Prerequisite table after:\n");
	printRel(cp);

	printf("\nExectuing insert((\"CS205\",\"CS101\"),CP)\n");
	printf("First, the Course-Prerequisite table before:\n");
	printRel(cp);
	rel_insert(cp, createTuple(2, "CS205", "CS101"));
	printf("Now, the Course-Prerequisite table after:\n");
	printRel(cp);

	//DEMONSTRATE SAVING FUNCTIONALITY
	
	//readd the deleted tuple so that it is normal
	rel_insert(cr, createTuple(2, "CS101", "Turing Aud."));

	printf("C. Brown's grade in CS101: ");
	whatGrade("C. Brown", "CS101", snap, csg);

	printf("\nL. Van Pelt's grade in PH100: ");
	whatGrade("L. Van Pelt", "PH100",snap, csg);

	printf("\nP. Patty's grade in CS101: ");
	whatGrade("P. Patty", "CS101", snap, csg);

	printf("\nC. Brown's location at 9AM on Monday: ");
	whereIs("C. Brown", "9AM", "M", cdh, snap, csg, cr);

	printf("\nP. Patty's location at 10AM on Wednesday: ");
	whereIs("P. Patty", "10AM", "W", cdh, snap, csg, cr);

	printf("\nL. Van Pelt's location at 10AM on Wednesday: ");
	whereIs("L. Van Pelt", "10AM", "W", cdh, snap, csg, cr);

	printf("\n\nResult of running selection on CSG with the condition Course=CS101\n");
	printRel(selection(csg, 0, 0, "CS101"));
	
	printf("\nResult of running selection on the previous table on the column of StudentID\n");
	int col[] = {0,1,0};
	printRel(project(selection(csg, 0,0,"CS101"), col));

	return 0;
}
