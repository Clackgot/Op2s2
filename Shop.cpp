#include "Shop.h"
#include <iostream>
#include <algorithm>
#include <direct.h>
#include <fstream>

Shop::Shop(std::string name)
{
	_name = name;
	char buff[66];
	char* temp = _getcwd(buff, sizeof(buff));
	_dataBase = buff;
	Shop::
	_dataBase += "\\db.txt";
	for (size_t i = 0; i < _dataBase.size(); i++)
	{
		if (_dataBase[i] == '\\')
		{
			_dataBase.insert(i, "\\");
			i++;
		}
	}
}

void Shop::pushBackGood(FoodGood good)
{
	foodGoods.push_back(good);
}

void Shop::pushBackGood(InstrumentalGood good)
{
	instrumentalGoods.push_back(good);
}





void Shop::printName()
{
	std::cout << _name << std::endl;
}

void Shop::printFoodGoods()
{
	for (auto& it : foodGoods)it.PrintGoodInfo();
}

void Shop::printInstrumentalGoods()
{
	for (auto& it : instrumentalGoods)it.PrintGoodInfo();
}

void Shop::printGoods()
{
	printFoodGoods();
	printInstrumentalGoods();
}

void Shop::RemoveFoodGoodByName(std::string foodName)
{
	bool once_find = false;

	auto item = find_if(Shop::foodGoods.begin(), Shop::foodGoods.end(),
		[&](FoodGood& d)->bool
		{
			return d.getName() == foodName;
		});

	if (item != Shop::foodGoods.end())
	{
		printf("Удалено:\n");
		(*item).PrintGoodInfo();
		Shop::foodGoods.erase(item);
	}
	else if(once_find)
	{
		RemoveFoodGoodByName(foodName);
	}
	else
	{
		printf("Такой продукт не найден\n");
		return;
	}
}

void Shop::RemoveInstrumentalGoodByWeight(float weight)
{
	bool once_find = false;

	auto item = find_if(Shop::instrumentalGoods.begin(), Shop::instrumentalGoods.end(),
		[&](InstrumentalGood& d)->bool
		{
			return d.getWeight() == weight;
		});

	if (item != Shop::instrumentalGoods.end())
	{
		printf("Удалено:\n");
		(*item).PrintGoodInfo();
		Shop::instrumentalGoods.erase(item);
	}
	else if (once_find)
	{
		RemoveInstrumentalGoodByWeight(weight);
	}
	else
	{
		printf("Такой инструмент не найден\n");
		return;
	}
}

void Shop::SortInstrumentalGoodsByWeight(int mode)
{
	if (mode == 1)sort(instrumentalGoods.begin(), instrumentalGoods.end(), [](InstrumentalGood a, InstrumentalGood b)->bool
		{
			return a.getWeight() > b.getWeight();
		});
	if (mode == 2)sort(instrumentalGoods.begin(), instrumentalGoods.end(), [](InstrumentalGood a, InstrumentalGood b)->bool
		{
			return a.getWeight() < b.getWeight();
		});
}

void Shop::SortFoodGoodsByFat(int mode)
{
	if (mode == 1)sort(foodGoods.begin(), foodGoods.end(), [](FoodGood a, FoodGood b)->bool
		{
			return a.getFat() > b.getFat();
		});
	if (mode == 2)sort(foodGoods.begin(), foodGoods.end(), [](FoodGood a, FoodGood b)->bool
		{
			return a.getFat() < b.getFat();
		});
}
void Shop::SortGoodsById(int mode)
{
	if (mode == 1)
	{
		sort(foodGoods.begin(), foodGoods.end(), [](FoodGood a, FoodGood b)->bool
			{
				return a.getId() > b.getId();
			});
		sort(instrumentalGoods.begin(), instrumentalGoods.end(), [](InstrumentalGood a, InstrumentalGood b)->bool
			{
				return a.getId() > b.getId();
			});
	}
	if (mode == 2)
	{
		sort(foodGoods.begin(), foodGoods.end(), [](FoodGood a, FoodGood b)->bool
			{
				return a.getId() < b.getId();
			});
		sort(instrumentalGoods.begin(), instrumentalGoods.end(), [](InstrumentalGood a, InstrumentalGood b)->bool
			{
				return a.getId() < b.getId();
			});
	}
}

void Shop::Load()
{
	Shop::foodGoods.clear();
	Shop::instrumentalGoods.clear();
	

	int type = -1;
	int id = -1;
	std::string name = "";
	int count = -1;
	float price = -1;
	
	int fat = -1;
	int protein = -1;
	int carbo = -1;

	std::string material = "";
	float volume = -1;
	float weight = -1;

	std::ifstream fp;
	fp.open(_dataBase);
	Good good;
	while (!fp.eof())
	{
		fp >> type;

		fp >> id;
		fp >> name;
		fp >> count;
		fp >> price;
		good = Good(id, name, count, price);
		if (type == 1)
		{
			fp >> fat;
			fp >> protein;
			fp >> carbo;
			foodGoods.push_back(FoodGood(good,fat,protein,carbo));
		}
		else if (type == 2)
		{
			fp >> material;
			fp >> volume;
			fp >> weight;
			instrumentalGoods.push_back(InstrumentalGood(good, material, volume, weight));
		}
	}
	fp.close();
}
void Shop::Save()
{
	this->SortGoodsById(2);//сортируем список по ID в порядке возрастания
	std::ofstream fp;
	fp.open(_dataBase, std::ios_base::trunc | std::ios::out);
	for (size_t i = 0; i < Shop::foodGoods.size(); i++)
	{
		fp << 1;
		fp << " ";

		fp << Shop::foodGoods[i].getId();
		fp << " ";

		fp << Shop::foodGoods[i].getName();
		fp << " ";

		fp << Shop::foodGoods[i].getCount();
		fp << " ";
		
		fp << Shop::foodGoods[i].getPrice();
		fp << " ";

		fp << Shop::foodGoods[i].getFat();
		fp << " ";

		fp << Shop::foodGoods[i].getProtein();
		fp << " ";

		fp << Shop::foodGoods[i].getCarbo();
		
		if (i == foodGoods.size()) 
		{
			fp << " ";
		}
		else
		{
			fp << std::endl;
		}
	}
	for (size_t i = 0; i < Shop::instrumentalGoods.size(); i++)
	{
		fp << 2;
		fp << " ";

		fp << Shop::instrumentalGoods[i].getId();
		fp << " ";

		fp << Shop::instrumentalGoods[i].getName();
		fp << " ";

		fp << Shop::instrumentalGoods[i].getCount();
		fp << " ";

		fp << Shop::instrumentalGoods[i].getPrice();
		fp << " ";

		fp << Shop::instrumentalGoods[i].getMaterial();
		fp << " ";

		fp << Shop::instrumentalGoods[i].getVolume();
		fp << " ";

		fp << Shop::instrumentalGoods[i].getWeight();

		if (i < instrumentalGoods.size()-1)
		{
			//fp << " ";
			fp << std::endl;
		}
	}
}
Good::Good(int id, std::string name, int count, float price)
{
	_id = id;
	if (name != "")_name = name;
	else _name = "None";
	if (count >= 0)_count = count;
	else count = 0;
	if (price > 0)_price = price;
	else price = 0;

}

Good::Good()
{
	_id = -1;
	_name = "Undefined";
	_count = -1;
	_price = -1.0f;

}

void Good::PrintGoodInfo()
{
	std::cout << "-------------" << _id << "----------------" << std::endl;
	
	std::cout << "Наименование:\t" << _name << std::endl;

	std::cout << "В наличии:\t" << _count << " ед." << std::endl;
	
	
	printf("Цена:\t\t%.2f руб.\n", _price);
	//std::cout << "Цена:\t\t" << _price << " руб." << std::endl;

}

std::string Good::getName()
{
	return _name;
}

int Good::getCount()
{
	return _count;
}

float Good::getPrice()
{
	return _price;
}

int Good::getId()
{
	return _id;
}





FoodGood::FoodGood(Good good, int fat, int protein, int carbo) : Good(good)
{
	if (fat >= 0)_fat = fat;
	else fat = 0;
	if (protein >= 0)_protein = protein;
	else protein = 0;
	if (carbo >= 0)_carbo = carbo;
	else carbo = 0;
}

FoodGood::FoodGood(int id, std::string name, int count, float price, int fat, int protein, int carbo) :Good(id, name, count, price)
{

	if (fat >= 0)_fat = fat;
	else fat = 0;
	if (protein >= 0)_protein = protein;
	else protein = 0;
	if (carbo >= 0)_carbo = carbo;
	else carbo = 0;

}

FoodGood::FoodGood()
{

}

void FoodGood::PrintGoodInfo()
{
	Good::PrintGoodInfo();
	float proteinPercent, fatPercent, carboPercent;
	proteinPercent = _protein*100 / (float)(_protein + _fat + _carbo);
	fatPercent = _fat*100 / (float)(_protein + _fat + _carbo);
	carboPercent = _carbo*100 / (float)(_protein + _fat + _carbo);
	//printf("%.2f%%", proteinPercent);
	printf("Тип:\t\tПродукт питания\n");
	printf("Белков:\t\t%d(%.2f%%)\nЖиров:\t\t%d(%.2f%%)\nУглеводов:\t%d(%.2f%%)\n", _protein,proteinPercent, _fat, fatPercent, _carbo, carboPercent);
}



int FoodGood::getFat()
{
	return _fat;
}

int FoodGood::getProtein()
{
	return _protein;
}

int FoodGood::getCarbo()
{
	return _carbo;
}


InstrumentalGood::InstrumentalGood(Good good, std::string material, float volume, float weight) :Good(good)
{
	if (material != "")_material = material;
	else _material = "None material";

	if (volume > 0)_volume = volume;
	else volume = 1;
	if (weight > 0)_weight = weight;
	else weight = 1;
}

InstrumentalGood::InstrumentalGood(int id, std::string name, int count, float price, std::string material, float volume, float weight) :Good(id, name, count, price)
{
	if (material != "")_material = material;
	else _material = "None material";

	if (volume > 0)_volume = volume;
	else volume = 1;
	if (weight > 0)_weight = weight;
	else weight = 1;
}

InstrumentalGood::InstrumentalGood()
{
}

void InstrumentalGood::PrintGoodInfo()
{
	Good::PrintGoodInfo();
	float density;
	density = _weight/ _volume;

	printf("Тип:\t\tИнструмент\n");
	printf("Масса:\t\t%.2f кг.\nПлотность:\t%.2f кг/м3.\n",_weight, density);
}

std::string InstrumentalGood::getMaterial()
{
	return _material;
}

float InstrumentalGood::getVolume()
{
	return _volume;
}

float InstrumentalGood::getWeight()
{
	return _weight;
}
