#include "PronadiPut.h"
#include<ctime>
#include<vector>
#include<list>
#include<queue>
using namespace std;

PronadiPut::PronadiPut(sf::RenderWindow* window)
{
	this->window = window;
}

void PronadiPut::KreirajMapu()
{
	srand(time(nullptr));
	pocetna.x = rnd_pozicija(0, 39);
	pocetna.y = rnd_pozicija(0, 59);
	ciljna.x = rnd_pozicija(0, 39);
	ciljna.y = rnd_pozicija(0, 59);

	for (unsigned i = 0; i < 40; i++)
	{
		for (unsigned j = 0; j < 60; j++)
		{
			polje.setSize(sf::Vector2f(20.f, 15.f));
			PostaviPocetnoStanje(i, j, polje);
			polje.setPosition(x, y);
			this->window->draw(polje);
			polja[i][j] = polje;
			x += 20;
		}

		y += 15;
		x = 0;
	}

	DodajPrepreke();
	polja[pocetna.x][pocetna.y].setFillColor(sf::Color::Red);
	polja[ciljna.x][ciljna.y].setFillColor(sf::Color::Red);
	PronadiNajboljiPut();
}

int PronadiPut::rnd_pozicija(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

void PronadiPut::PostaviPocetnoStanje(int i, int j, sf::RectangleShape& polje)
{
	if ((i == pocetna.x && j == pocetna.y) || (i == ciljna.x && j == ciljna.y))
	{
		polje.setFillColor(sf::Color::Red);
	}
	else {
		polje.setFillColor(sf::Color::Black);
	}
}

void PronadiPut::DodajPrepreke()
{
	for (unsigned i = 0; i < 300; i++)
	{
		polja[rnd_pozicija(0, 39)][rnd_pozicija(0, 59)].setFillColor(sf::Color::Yellow);
	}
}

bool PronadiPut::jeliCiljna(int i, int j)
{
	if (i == ciljna.x && j == ciljna.y)
	{
		return true;
	}

	return false;
}

bool PronadiPut::jeliPocetna(int i, int j)
{
	if (i == pocetna.x && j == pocetna.y)
	{
		return true;
	}

	return false;
}

bool PronadiPut::jeliPrepreka(int i, int j)
{
	if (polja[i][j].getFillColor() == sf::Color::Yellow)
	{
		return true;
	}

	return false;
}

void PronadiPut::PronadiNajboljiPut()
{
	vector<vector<bool>> provjereni(40, vector<bool>(60, false));
	vector<vector<pair<int, int>>> paroviPolja(40, vector<pair<int, int>>(60));

	provjereni[pocetna.x][pocetna.y] = true;
	paroviPolja[pocetna.x][pocetna.y] = make_pair(-1, -1);

	queue<pair<int, int>> q;
	pair<int, int> tocka;

	int i = pocetna.x;
	int j = pocetna.y;

	q.push(make_pair(pocetna.x, pocetna.y));

	while (!q.empty())
	{
		tocka = q.front();

		i = tocka.first;
		j = tocka.second;

		if (!jeliCiljna(i, j))
		{
			q.pop();

			if (i > 0 && !jeliPrepreka(i - 1, j))
			{
				if (!provjereni[i - 1][j])
				{
					paroviPolja[i - 1][j] = make_pair(i, j);
					provjereni[i - 1][j] = true;
					q.push(make_pair(i - 1, j));
				}
			}

			if (i < 39 && !jeliPrepreka(i + 1, j))
			{
				if (!provjereni[i + 1][j])
				{
					paroviPolja[i + 1][j] = make_pair(i, j);
					provjereni[i + 1][j] = true;
					q.push(make_pair(i + 1, j));
				}
			}

			if (j > 0 && !jeliPrepreka(i, j - 1))
			{
				if (!provjereni[i][j - 1])
				{
					paroviPolja[i][j - 1] = make_pair(i, j);
					provjereni[i][j - 1] = true;
					q.push(make_pair(i, j - 1));
				}
			}

			if (j < 59 && !jeliPrepreka(i, j + 1))
			{
				if (!provjereni[i][j + 1])
				{
					paroviPolja[i][j + 1] = make_pair(i, j);
					provjereni[i][j + 1] = true;
					q.push(make_pair(i, j + 1));
				}
			}
		}
		else
		{
			break;
		}
	}

	if (jeliCiljna(i, j))
	{
		i = paroviPolja[tocka.first][tocka.second].first;
		j = paroviPolja[tocka.first][tocka.second].second;

		while (!jeliPocetna(i, j))
		{
			polja[i][j].setFillColor(sf::Color::Green);
			tocka = make_pair(i, j);
			i = paroviPolja[tocka.first][tocka.second].first;
			j = paroviPolja[tocka.first][tocka.second].second;
		}
	}
}

void PronadiPut::iscrtaj()
{
	for (unsigned i = 0; i < 40; i++)
	{
		for (unsigned j = 0; j < 60; j++)
		{
			this->window->draw(polja[i][j]);
		}
	}
}
