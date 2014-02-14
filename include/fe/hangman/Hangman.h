#ifndef __HANGMAN_H__
#define __HANGMAN_H__

namespace fe
{

class Hangman
{
public:
	Hangman();
	Hangman(const Hangman& toCopy);
	Hangman& operator=(const Hangman& toCopy);
	~Hangman();
};

}

#endif
