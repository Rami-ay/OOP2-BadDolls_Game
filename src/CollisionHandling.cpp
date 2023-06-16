#include "CollisionHandling.h"
#include "GameObject.h"
#include "FirstPlayer.h"
#include "SecondPlayer.h"
#include "Wall.h"
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <typeinfo>
#include <typeindex>
#include "Enemy.h"
#include "Heart.h"
#include "EnemyBear.h"
#include "EnemyBat.h"
#include "Coin.h"
#include "Gun.h"
#include <memory>
namespace // anonymous namespace — the standard way to make function "static"
{

    // primary collision-processing functions
    void firstPlayer2Wall(GameObject& firstPlayer,
        GameObject& wall)
    {
        firstPlayer.setPosition(firstPlayer.getPrevPosition());
    }

    void wall2FirstPlayer(GameObject& wall,
        GameObject& firstPlayer)
    {
        firstPlayer2Wall(firstPlayer, wall);
    }

    void secondPlayer2Wall(GameObject& secondPlayer,
        GameObject& wall)
    {
        secondPlayer.setPosition(secondPlayer.getPrevPosition());
    }

    void wall2SecondPlayer(GameObject& wall,
        GameObject& secondPlayer)
    {
       secondPlayer2Wall(secondPlayer, wall);

    }

    void firstPlayer2SecondPlayer(GameObject& firstPlayer,  
        GameObject& secondPlayer)
    {
        firstPlayer.setPosition(firstPlayer.getPrevPosition());
        secondPlayer.setPosition(secondPlayer.getPrevPosition());
    }

    void secondPlayer2FirstPlayer(GameObject& secondPlayer,
        GameObject& firstPlayer)
    {
        firstPlayer2SecondPlayer(firstPlayer, secondPlayer);
    }


    void firstPlayer2Heart(GameObject& firstPlayer, GameObject& heart)
    {
        FirstPlayer& firstPlayerObject = dynamic_cast<FirstPlayer&>(firstPlayer);
        firstPlayerObject.setHealth(30);

        Heart& heartObject = dynamic_cast<Heart&>(heart);  
        heartObject.deleteObject(); 
        std::cout << firstPlayerObject.getHealth() << std::endl;
    }

    void heart2FirstPlayer(GameObject& heart,
        GameObject& firstPlayer)
    {
        firstPlayer2SecondPlayer(firstPlayer, heart);
    }

    void secondPlayer2Heart(GameObject& secondPlayer,
        GameObject& heart)
    {
        SecondPlayer& secondPlayerObject = dynamic_cast<SecondPlayer&>(secondPlayer);
        secondPlayerObject.setHealth(30);

        Heart& heartObject = dynamic_cast<Heart&>(heart);
        heartObject.deleteObject();

        std::cout << secondPlayerObject.getHealth() << std::endl;
    }

    void heart2SecondPlayer(GameObject& heart,
        GameObject& secondPlayer)
    {
        firstPlayer2SecondPlayer(secondPlayer, heart);
    }

    void enemyBear2Wall(GameObject& enemy,
        GameObject& wall)
    {
        enemy.setPosition(enemy.getPrevPosition());
    }

    void wall2EnemyBear(GameObject& wall,
        GameObject& enemy)
    {
        enemyBear2Wall(enemy, wall);
    }
    void firstPlayer2Coin(GameObject& firstPlayer, GameObject& coin)
    {
        FirstPlayer& firstPlayerObject = dynamic_cast<FirstPlayer&>(firstPlayer);
        firstPlayerObject.setCoins(20);

        Coin& coinObject = dynamic_cast<Coin&>(coin);
        coinObject.deleteObject();

        std::cout << firstPlayerObject.getCoins() << std::endl;
    }

    void coin2FirstPlayer(GameObject& coin,
        GameObject& firstPlayer)
    {
        firstPlayer2Coin(firstPlayer, coin);
    }

    void secondPlayer2Coin(GameObject& secondPlayer,
        GameObject& coin)
    {
        SecondPlayer& secondPlayerObject = dynamic_cast<SecondPlayer&>(secondPlayer);
        secondPlayerObject.setCoins(20);

        Coin& coinObject = dynamic_cast<Coin&>(coin);
        coinObject.deleteObject();

        std::cout << secondPlayerObject.getCoins() << std::endl;
    }

    void coin2SecondPlayer(GameObject& coin,
        GameObject& secondPlayer)
    {
        secondPlayer2Coin(secondPlayer, coin);
    }

    void enemyBear2Heart(GameObject& enemy,
        GameObject& heart)
    {
    }

    void heart2EnemyBear(GameObject& heart,
        GameObject& enemy)
    {
        enemyBear2Heart(enemy, heart);
    }

    void enemyBear2Coin(GameObject& enemy,
        GameObject& coin)
    {

    }

    void coin2EnemyBear(GameObject& coin,
        GameObject& enemy)
    {
        enemyBear2Coin(enemy, coin);
    }

    void firstPlayer2Gun(GameObject& firstPlayer,
        GameObject& gun)
    {
        FirstPlayer& firstPlayerObject = dynamic_cast<FirstPlayer&>(firstPlayer);
        Gun& gunObject = dynamic_cast<Gun&>(gun);

        gunObject.deleteObject();
        firstPlayerObject.addGun(gunObject);
    }
        

 

    void gun2FirstPlayer(GameObject& gun,
        GameObject& firstPlayer)
    {
        firstPlayer2Gun(firstPlayer, gun);
    }

    void firstPlayer2EnemyBat(GameObject& firstPlayer,
        GameObject& enemyBat)
    {
        FirstPlayer& firstPlayerObject = dynamic_cast<FirstPlayer&>(firstPlayer);
        firstPlayerObject.decreaseHealth(50);

        EnemyBat& enemyBatObject = dynamic_cast<EnemyBat&>(enemyBat);
        enemyBatObject.decreaseHealth(150);

        std::cout << firstPlayerObject.getHealth() << " " << enemyBatObject.getHealth() << std::endl;
    }

    void enemyBat2FirstPlayer(GameObject& enemyBat,
        GameObject& firstPlayer)
    {
        firstPlayer2EnemyBat(firstPlayer, enemyBat);
    }

    using HitFunctionPtr = std::function<void(GameObject&, GameObject&)>;
    // typedef void (*HitFunctionPtr)(GameObject&, GameObject&);
    using Key = std::pair<std::type_index, std::type_index>;
    // std::unordered_map is better, but it requires defining good hash function for pair
    using HitMap = std::map<Key, HitFunctionPtr>;

    HitMap initializeCollisionMap()
    {
        HitMap phm;
        phm[Key(typeid(FirstPlayer), typeid(Wall))] = &firstPlayer2Wall;
        phm[Key(typeid(Wall), typeid(FirstPlayer))] = &wall2FirstPlayer;

        phm[Key(typeid(FirstPlayer), typeid(SecondPlayer))] = &firstPlayer2SecondPlayer;
        phm[Key(typeid(SecondPlayer), typeid(FirstPlayer))] = &secondPlayer2FirstPlayer;

        phm[Key(typeid(SecondPlayer), typeid(Wall))] = &secondPlayer2Wall;
        phm[Key(typeid(Wall), typeid(SecondPlayer))] = &wall2SecondPlayer;

        phm[Key(typeid(FirstPlayer), typeid(Heart))] = &firstPlayer2Heart;
        phm[Key(typeid(Heart), typeid(FirstPlayer))] = &heart2FirstPlayer;

        phm[Key(typeid(SecondPlayer), typeid(Heart))] = &secondPlayer2Heart;
        phm[Key(typeid(Heart), typeid(SecondPlayer))] = &heart2SecondPlayer;

        phm[Key(typeid(EnemyBear), typeid(Wall))] = &enemyBear2Wall;
        phm[Key(typeid(Wall), typeid(EnemyBear))] = &wall2EnemyBear;

        phm[Key(typeid(FirstPlayer), typeid(Coin))] = &firstPlayer2Coin;
        phm[Key(typeid(Coin), typeid(FirstPlayer))] = &coin2FirstPlayer;

        phm[Key(typeid(SecondPlayer), typeid(Coin))] = &secondPlayer2Coin;
        phm[Key(typeid(Coin), typeid(SecondPlayer))] = &coin2SecondPlayer;

        phm[Key(typeid(EnemyBear), typeid(Heart))] = &enemyBear2Heart;
        phm[Key(typeid(Heart), typeid(EnemyBear))] = &heart2EnemyBear;

        phm[Key(typeid(EnemyBear), typeid(Coin))] = &enemyBear2Coin;
        phm[Key(typeid(Coin), typeid(EnemyBear))] = &coin2EnemyBear;

        phm[Key(typeid(FirstPlayer), typeid(Gun))] = &firstPlayer2Gun;
        phm[Key(typeid(Gun), typeid(FirstPlayer))] = &gun2FirstPlayer;

        phm[Key(typeid(FirstPlayer), typeid(EnemyBat))] = &firstPlayer2EnemyBat;
        phm[Key(typeid(EnemyBat), typeid(FirstPlayer))] = &enemyBat2FirstPlayer;
        return phm;
    }

    HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2)
    {
        static HitMap collisionMap = initializeCollisionMap();
        auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
        if (mapEntry == collisionMap.end())
        {
            return nullptr;
        }
        return mapEntry->second;
    }
}

 // end namespace

void processCollision(GameObject& object1, GameObject& object2)
{
    auto phf = lookup(typeid(object1), typeid(object2));
    if (!phf)
    {
        throw UnknownCollision(object1, object2);
    }
    phf(object1, object2);
}
