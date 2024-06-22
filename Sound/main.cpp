#include <iostream>
#include <fstream>
#include "FileSound.h"
#include "PeriodicSound.h"
#include "Vector.h"
#include "MixSound.h"
#include "SoundContainer.h"
#include "SequenceSound.h"
#include "Effects.h"
#include "Playlist.h"


void createFileTest(const char* file)
{
	std::ofstream oFile(file, std::ios::binary);

	const std::size_t size = 25;

	oFile.write(reinterpret_cast<const char*>(&size), sizeof(size));


	for (double i = 0; i < size; i++)
	{
		oFile.write(reinterpret_cast<const char*>(&i), sizeof(i));
	}

	oFile.close();
}


int main()
{
	createFileTest("test.bin");

	FileSound<double> f1(30, "test.bin");
	std::cout << f1;

	Vector<double> samples;
	for (size_t i = 0; i < 10; i++)
	{
		samples.push_back(i);
	}

	PeriodicSound<double> p1(30, samples, 3);
	std::cout << p1;

	SoundContainer<double> sounds;
	sounds.push_back(&f1);
	sounds.push_back(&p1);

	MixSound<double> m1(30, sounds);
	std::cout << m1;

	SequenceSound<double> s1(30, sounds);
	std::cout << s1;

	Effect<double, Amplify<double>> a1 = Effects<double>::amplifyEffect(f1, 2);
	Effect<double, Amplify<double>> a2 = Effects<double>::amplifyEffect(f1, -2);

	Effect<double, Amplify<double>> a3 = Effects<double>::amplifyEffect(f1, 0);

	SoundContainer<double> sounds1;
	sounds1.push_back(&a1);
	sounds1.push_back(&a2);


	MixSound<double> m2(30, sounds1);

	std::cout << a1;
	std::cout << a2;
	std::cout << a3;
	std::cout << m2;

	Playlist<double> playlist(100, "playlist.txt");
	playlist.print();

	return 0;
}