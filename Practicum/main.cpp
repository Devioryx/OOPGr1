#include <iostream>
#include "Person.h"
#include "Group.h"
#include "Team.h"

int main()
{
	Person p1("Gosho", "Sava", "Rakovski", 8739287463);
	Person p2("Pesho", "Petrov", "Georgiev", 8787327463);
	Person p3("Kristo", "Idealov", "Minkov", 8987327463);


	Team t;
	t += p1;
	t += p2;
	t += p3;


	t(p1, p2);
	t(p2, p3);
	t(p3, p1);

	std::cout << t;


	Team t1;


	Person p4("Indil", "Retor", "Mekov", 8736538463);
	Person p5("Idev", "Kadov", "Radov", 8798727463);
	Person p6("Peko", "Cenov", "Qkov", 8987377773);
	Person p7("Keko", "Cenov", "Qkov", 8987653573);
	Person p8("Reko", "Cenov", "Qkov", 8987478773);

	t1 += p4;
	t1 += p5;
	t1 += p6;
	t1 += p7;
	t1 += p8;

	t1(p4, p5);
	t1(p5, p6);
	t1(p6, p7);
	t1(p7, p8);

	//t1(p6, p4);
	

	//std::cout << (t > t1) << std::endl;
	std::cout << t1;


}	