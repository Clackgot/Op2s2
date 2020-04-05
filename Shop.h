#pragma once
#include <string>
#include <vector>

class Good {
private:
	int _id;
	std::string _name;
	int _count;
	float _price;
protected:
	void PrintGoodInfo();
public:
	Good(int id, std::string name, int count, float price);
	Good();

	int getId();
	std::string getName();
	int getCount();
	float getPrice();
	
};

class FoodGood: public Good
{
private:
	int _fat = -1;
	int _protein = -1;
	int _carbo = -1;

public:
	FoodGood(Good good, int fat, int protein, int carbo);

	FoodGood(int id, std::string name, int count, float price, int fat, int protein, int carbo);
	FoodGood();
	void PrintGoodInfo();
	int getFat();
	int getProtein();
	int getCarbo();
};

class InstrumentalGood : public Good
{
private:
	std::string _material;
	float _volume = -1;
	float _weight = -1;

public:
	InstrumentalGood(Good good,std::string material, float volume, float weight);
	///<summary>
	/// Конструктор инструмента
	///</summary>
	///<param name="id">Номер</param>
	///<param name="name">Наименование</param>
	///<param name="count">Количество</param>
	///<param name="price">Цена</param>
	///<param name="material">Материал инструмента</param>
	///<param name="volume">Объем(м3)</param>
	///<param name="weight">Масса(кг)</param>
	InstrumentalGood(int id, std::string name, int count, float price, std::string material, float volume, float weight);
	InstrumentalGood();
	void PrintGoodInfo();

	std::string getMaterial();
	float getVolume();
	float getWeight();
};

class Shop
{
private:
	std::string _dataBase = "";
	std::string _name;
	std::vector<FoodGood> foodGoods;
	std::vector<InstrumentalGood> instrumentalGoods;
public:


	Shop(std::string name);
	void pushBackGood(FoodGood good);
	void pushBackGood(InstrumentalGood good);
	void printName();
	void printFoodGoods();
	void printInstrumentalGoods();
	void printGoods();

	void RemoveFoodGoodByName(std::string foodName);
	void SortFoodGoodsByFat(int mode);

	void RemoveInstrumentalGoodByWeight(float weight);
	void SortInstrumentalGoodsByWeight(int mode);

	

	


	void SortGoodsById(int mode);

	void Load();
	void Save();
};