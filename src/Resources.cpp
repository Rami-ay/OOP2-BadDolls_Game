#include "Resources.h"
namespace
{
    AnimationData FirstPlayerData()
    {
        const auto size = sf::Vector2i(32, 32);
        const auto initSpace = sf::Vector2i(96, 128);
        const auto middleSpace = sf::Vector2i(0, 0);
        auto firstPlayer = AnimationData{};
        auto currentStart = initSpace;

        auto nextStart = [&]()
        {
            //currentStart += middleSpace;
            currentStart.x += size.x;
            return currentStart;
        };

        firstPlayer.m_data[Direction::Down].emplace_back(currentStart, size);
        firstPlayer.m_data[Direction::Down].emplace_back(nextStart(), size);
        firstPlayer.m_data[Direction::Down].emplace_back(nextStart(), size);
        currentStart.x = 96;
        currentStart.y += size.y;
        firstPlayer.m_data[Direction::Left].emplace_back(currentStart, size);
        firstPlayer.m_data[Direction::Left].emplace_back(nextStart(), size);
        firstPlayer.m_data[Direction::Left].emplace_back(nextStart(), size);
        currentStart.x = 96;
        currentStart.y += size.y;
        firstPlayer.m_data[Direction::Right].emplace_back(currentStart, size);
        firstPlayer.m_data[Direction::Right].emplace_back(nextStart(), size);
        firstPlayer.m_data[Direction::Right].emplace_back(nextStart(), size);
        currentStart.x = 96;
        currentStart.y += size.y;
        firstPlayer.m_data[Direction::Up].emplace_back(currentStart, size);
        firstPlayer.m_data[Direction::Up].emplace_back(nextStart(), size);
        firstPlayer.m_data[Direction::Up].emplace_back(nextStart(), size);


        return firstPlayer;
    }
    AnimationData SecondPlayerData()
    {
        const auto size = sf::Vector2i(32, 32);
        const auto initSpace = sf::Vector2i(0, 0);
        const auto middleSpace = sf::Vector2i(0, 0);
        auto secondPlayer = AnimationData{};
        auto currentStart = initSpace;

        auto nextStart = [&]()
        {
            //currentStart += middleSpace;
            currentStart.x += size.x;
            return currentStart;
        };
        secondPlayer.m_data[Direction::Down].emplace_back(currentStart, size);
        secondPlayer.m_data[Direction::Down].emplace_back(nextStart(), size);
        secondPlayer.m_data[Direction::Down].emplace_back(nextStart(), size);
        currentStart.x = 0;
        currentStart.y += size.y;
        secondPlayer.m_data[Direction::Left].emplace_back(currentStart, size);
        secondPlayer.m_data[Direction::Left].emplace_back(nextStart(), size);
        secondPlayer.m_data[Direction::Left].emplace_back(nextStart(), size);
        currentStart.x = 0;
        currentStart.y += size.y;
        secondPlayer.m_data[Direction::Right].emplace_back(currentStart, size);
        secondPlayer.m_data[Direction::Right].emplace_back(nextStart(), size);
        secondPlayer.m_data[Direction::Right].emplace_back(nextStart(), size);
        currentStart.x = 96;
        currentStart.y += size.y;
        secondPlayer.m_data[Direction::Up].emplace_back(currentStart, size);
        secondPlayer.m_data[Direction::Up].emplace_back(nextStart(), size);
        secondPlayer.m_data[Direction::Up].emplace_back(nextStart(), size);


        return secondPlayer;
    }
    AnimationData EnemyBearData()
    {
        const auto size = sf::Vector2i(32, 32);
        const auto initSpace = sf::Vector2i(0, 96);
        const auto middleSpace = sf::Vector2i(0, 0);
        auto enemyBear = AnimationData{};
        auto currentStart = initSpace;

        auto nextStart = [&]()
        {
            //currentStart += middleSpace;
            currentStart.x += size.x;
            return currentStart;
        };

        enemyBear.m_data[Direction::Right].emplace_back(currentStart, size);
        for (int i = 0; i < 12; ++i) {
            enemyBear.m_data[Direction::Right].emplace_back(nextStart(), size);
        }

        currentStart = sf::Vector2i(0, 96);

        // Create left-direction frames as a reflection of the right-direction frames
        for (const auto& frame : enemyBear.m_data[Direction::Right]) {
            sf::IntRect flippedFrame(frame.left + frame.width, frame.top, -frame.width, frame.height);
            enemyBear.m_data[Direction::Left].emplace_back(flippedFrame);
        }


        currentStart = sf::Vector2i(0, 96);
        enemyBear.m_data[Direction::Up].emplace_back(currentStart, size);
        for (int i = 0; i < 12; ++i) {
            enemyBear.m_data[Direction::Up].emplace_back(nextStart(), size);
        }

        currentStart = sf::Vector2i(0, 96);
        enemyBear.m_data[Direction::Down].emplace_back(currentStart, size);
        for (int i = 0; i < 12; ++i) {
            enemyBear.m_data[Direction::Down].emplace_back(nextStart(), size);
        }


        return enemyBear;
    }

    AnimationData HeartData()
    {
        const auto size = sf::Vector2i(32, 32);
        const auto initSpace = sf::Vector2i(0, 0);
        const auto middleSpace = sf::Vector2i(0, 0);
        auto heart = AnimationData{};
        auto currentStart = initSpace;

        auto nextStart = [&]()
        {
            //currentStart += middleSpace;
            currentStart.x += size.x;
            return currentStart;
        };
        heart.m_data[Direction::Stay].emplace_back(currentStart, size);
        for (int i = 0; i < 7; ++i) {
            heart.m_data[Direction::Stay].emplace_back(nextStart(), size);
        }
        currentStart = sf::Vector2i(0, 32);
        heart.m_data[Direction::Stay].emplace_back(currentStart, size);
        for (int i = 0; i < 7; ++i) {
            heart.m_data[Direction::Stay].emplace_back(nextStart(), size);
        }
        return heart;
    }

    AnimationData CoinData()
    {
        const auto size = sf::Vector2i(32, 32);
        const auto initSpace = sf::Vector2i(0, 0);
        const auto middleSpace = sf::Vector2i(0, 0);
        auto coin = AnimationData{};
        auto currentStart = initSpace;

        auto nextStart = [&]()
        {
            //currentStart += middleSpace;
            currentStart.x += size.x;
            return currentStart;
        };
        coin.m_data[Direction::Stay].emplace_back(currentStart, size);
        for (int i = 0; i < 4; ++i) {
            coin.m_data[Direction::Stay].emplace_back(nextStart(), size);
        }
        currentStart = sf::Vector2i(0, 32);
        coin.m_data[Direction::Stay].emplace_back(currentStart, size);
        for (int i = 0; i < 4; ++i) {
            coin.m_data[Direction::Stay].emplace_back(nextStart(), size);
        }
        return coin;
    }

    AnimationData BatData()
    {
        const auto size = sf::Vector2i(32, 32);
        const auto initSpace = sf::Vector2i(0, 32);
        const auto middleSpace = sf::Vector2i(0, 0);
        auto bat = AnimationData{};
        auto currentStart = initSpace;

        auto nextStart = [&]()
        {
            //currentStart += middleSpace;
            currentStart.x += size.x;
            return currentStart;
        };
        bat.m_data[Direction::Right].emplace_back(currentStart, size);
        for (int i = 0; i < 3; ++i) {
            bat.m_data[Direction::Right].emplace_back(nextStart(), size);
        }
        currentStart = sf::Vector2i(0, 96);
        bat.m_data[Direction::Left].emplace_back(currentStart, size);
        for (int i = 0; i < 3; ++i) {
            bat.m_data[Direction::Left].emplace_back(nextStart(), size);
        }
        return bat;
    }
}
Resources::Resources():m_animationData(Max)
{
    m_levels = readNamesVector("levels.txt"); //read the levels names from the levels file
    std::vector<std::string> texturesNames = readNamesVector("allTextures.txt"); //read the textures names from allTextures file
   // std::vector<std::string> soundsNames = readNamesVector("allSounds.txt"); //read the sounds names from sounds file
    m_textures = getTexturesVector(texturesNames); //get the images textures from the images file
   // m_buffers = fillBufferVector(soundsNames);
    //m_sounds = fillSoundsVector(m_buffers);


    m_playersNames = readNamesVector("PlayersNames.txt"); //read the players names from PlayersNames file
   /* if (!m_texture.loadFromFile("Player.png"))
    {
        throw std::runtime_error("Can't load file");
    }*/
    m_font.loadFromFile("arial.ttf");
    m_animationData[FirstPlayer] = FirstPlayerData();
    m_animationData[SecondPlayer] = SecondPlayerData();
    m_animationData[EnemyBear] = EnemyBearData();
    m_animationData[Heart] = HeartData();
    m_animationData[Coin] = CoinData();
    m_animationData[EnemyBat] = BatData();
}
Resources& Resources::instance()
{
    static Resources instance;
    return instance;
}

//return vector of textures
const std::vector<sf::Texture>& Resources::getTextures() const
{
    return m_textures;
}
//
////return a specific texture
//const sf::Texture& Resources::getTexture(const int index) const
//{
//    return m_textures[index];
//}

//return the current level
int Resources::getCurrentLevel() const
{
    std::ifstream file;
    char level;

    //opens the file
    file.open("currentLevel.txt");
    if (!file.is_open()) {
        std::cerr << "input file not found" << std::endl;
        exit(EXIT_FAILURE);
    }

    file.get(level);
    file.close();

    return level - '0'; //to return the number of the level , for example if the level is 1 (char) then we
    // decrease the char 0 and we get 1(int)
}

//const std::vector<sf::Font>& Resources::getFonts() const
//{
//    return m_Fonts;
//}
const sf::Font& Resources::getFont() const
{
    return m_font;
}

const std::string& Resources::getLevel(const int index) const
{
    return m_levels[index];
    
}


const std::vector<std::string> Resources::getPlayers() const
{
    return m_playersNames;
}

//to print the current level number on the currentLevel file
void Resources::saveCurrentLevel(const int num)
{
    std::ofstream file;

    //opens the file
    file.open("..\\..\\..\\resources\\textFiles\\currentLevel.txt");
    if (!file.is_open()) {
        std::cerr << "input file not found" << std::endl;
        exit(EXIT_FAILURE);
    }

    file << num;
    file.close();
}

//return a vector of strings that read from text
std::vector<std::string> Resources::readNamesVector(const char file_name[]) const
{
    std::ifstream file;
    std::vector<std::string> names;

    //opens the file
    file.open(file_name);
    if (!file.is_open()) {
        std::cerr << "input file not found" << std::endl;
        exit(EXIT_FAILURE);
    }

    //reads the image's name
    for (auto line = std::string(); std::getline(file, line);)
    {
        names.push_back(line);
    }

    file.close();

    return names;
}

//retur a vector of textures
std::vector<sf::Texture> Resources::getTexturesVector(const std::vector<std::string>& names) const
{
    std::vector<sf::Texture> textures(names.size());

    for (int i = 0; i < names.size(); i++)
        textures[i].loadFromFile(names[i]);

    return textures;
}

//return a vector of sounds
std::vector<sf::Sound> Resources::fillSoundsVector(const std::vector<sf::SoundBuffer>& buffer) const
{
    std::vector<sf::Sound> sounds(buffer.size());

    for (int i = 0; i < buffer.size(); i++)
        sounds[i].setBuffer(buffer[i]);

    return sounds;
}

//return a vector of buffers
std::vector<sf::SoundBuffer> Resources::fillBufferVector(const std::vector<std::string>& names) const
{
    std::vector<sf::SoundBuffer> buffers(names.size());
    sf::SoundBuffer buffer;

    for (int i = 0; i < names.size(); i++)
    {
        buffers[i].loadFromFile(names[i]);
    }

    return buffers;
}


//to build the map from a text file
std::vector<std::string> Resources::buildMap(const int level)
{
    std::ifstream file;
    std::vector<std::string> map;
    auto time = std::string();

    //opens the file
    file.open(getLevel(level));
    if (!file.is_open()) {
        std::cerr << level << " file not found" << std::endl;
        exit(EXIT_FAILURE);
    }

    //std::getline(file, time);
   // m_levelTime = (float)std::stoi(time); //stoi : to convert a string to integer

    //reads the map
    for (auto line = std::string(); std::getline(file, line);)
    {
        map.push_back(line);
    }

    file.close();

    return map;
}

//the music of the background
//void Resources::playMusic()
//{
//    m_sounds[background].setLoop(true);// play all the time
//    m_sounds[background].setVolume(8);
//    m_sounds[background].play();
//}

//play a specific sound
//void Resources::playSound(const int index)
//{
//    m_sounds[index].setVolume(15);
//    m_sounds[index].play();
//}
