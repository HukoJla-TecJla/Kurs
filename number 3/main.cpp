#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
//Класс с персонажами 
enum class Characters
{
    Defender = 1,
    Healer,
    MeleeFigher,
    RangedFigher
};

//Класс с общими характеристиками
class Characteristics {
public:
    int health;
    int armor;
    int strength;
    int intelligence;
    int agility;
    int accuracy;
    int luck;
    int mastery;
};

//Класс для конструкции характеристик персонажа
class Equipment {
private:
    
public:
    virtual void AddCharacteristics(Characteristics& SetCharacteristics) const = 0;
};


//Добавление оружия персонажу
class Weapons : Equipment {
private:
    int Damages;
public:
    Weapons(int damages) : Damages(damages) {}
    void AddCharacteristics(Characteristics& SetCharacteristics) const override
    {
        SetCharacteristics.strength += Damages;
    }
};


//Добавление шлема
class Helmet : Equipment {
private:
    int Armor;
public:
    Helmet(int armor) : Armor(armor) {}
    void AddCharacteristics(Characteristics& SetCharacteristics) const override
    {
        SetCharacteristics.armor += Armor;
    }
};


//Добавление бронежилета
class BulletproofVest : Equipment {
private:
    int Armor;
public:
    BulletproofVest(int armor) : Armor(armor) {}
    void AddCharacteristics(Characteristics& SetCharacteristics) const override
    {
        SetCharacteristics.armor += Armor;
    }
};

class Character {
private:
    Characters characters;
    Characteristics characteristics;
    std::vector <Equipment*> equipment;
    int damage;
    int protection;

    void CalculationDamage()
    {
        if (characteristics.strength + characteristics.luck > 100)
        {
            damage = characteristics.strength * 2;
        }
        else
        {
            damage = characteristics.strength + characteristics.luck;
        }
    }

    void CalculationProtection()
    {
        protection = characteristics.armor + characteristics.mastery;
    }
public:
    Character(Characters Characters): characters(Characters) {
        if (characters == Characters::Defender)
        {
            characteristics.accuracy = 70;
            characteristics.agility = 90;
            characteristics.armor = 10;
            characteristics.health = 100;
            characteristics.intelligence = 20;
            characteristics.luck = 15;
            characteristics.mastery = 70;
            characteristics.strength = 100;
        }
        if (characters == Characters::Healer)
        {
            characteristics.accuracy = 10;
            characteristics.agility = 50;
            characteristics.armor = 10;
            characteristics.health = 100;
            characteristics.intelligence = 100;
            characteristics.luck = 90;
            characteristics.mastery = 50;
            characteristics.strength = 20;
        }
        if (characters == Characters::MeleeFigher)
        {
            characteristics.accuracy = 30;
            characteristics.agility = 100;
            characteristics.armor = 10;
            characteristics.health = 100;
            characteristics.intelligence = 50;
            characteristics.luck = 30;
            characteristics.mastery = 70;
            characteristics.strength = 100;
        }
        if (characters == Characters::RangedFigher)
        {
            characteristics.accuracy = 100;
            characteristics.agility = 30;
            characteristics.armor = 10;
            characteristics.health = 100;
            characteristics.intelligence = 100;
            characteristics.luck = 30;
            characteristics.mastery = 70;
            characteristics.strength = 50;
        }
    }

    void AddEquip(Equipment* equip)
    {
        equipment.push_back(equip);
        equip->AddCharacteristics(characteristics);
    }

    int GetLevel()
    {
        CalculationDamage();
        CalculationProtection();
        return characteristics.accuracy + characteristics.agility + characteristics.armor + characteristics.health + characteristics.intelligence + characteristics.luck + characteristics.mastery + characteristics.strength + damage + protection;
    }

    int GetDamage() { return damage; }
    int GetProtection() { return protection; }

};


int main()
{
    system("color F0");

    // Создание персонажа
    int character;

    std::cout << "Character:\n1)Defender\n2)Healer\n3)MeleeFighter\n4)RangedFighter\nTake character's class: ";
    std::cin >> character;

    Characters charclass = Characters(character);
    Character player(charclass);

    // Создание генератора для оружия и брони
    //WeaponGenerator weaponGenerator;
   // ArmorGenerator armorGenerator;

    // Генерация случайного оружия и брони
    //Equipment* weapon = weaponGenerator.generateEquipment();
    //Equipment* armor = armorGenerator.generateEquipment();

    // Экипировка персонажа
    //player.equip(weapon);
    //player.equip(armor);

    // Расчет урона
    int level = player.GetLevel();
    int damage = player.GetDamage();
    int protection = player.GetProtection();

    std::cout << "Damage: " << damage << "\n";
    std::cout << "Protection: " << protection << "\n";
    std::cout << "Level: " << level << "\n";
}
