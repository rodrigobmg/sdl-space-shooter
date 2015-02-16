/*******************************************************************//*
 * Implementation of the Level class.
 *
 * @author      Brandon To
 * @version     1.0
 * @since       2015-02-14
 * @modified    2015-02-16
 *********************************************************************/
#include "Level.h"

#include "tinyxml.h"

Level::Level()
:   currentLevel(0),
    doneLevel(true),
    nextSpawnTime()
{
    levelXmlPaths[0] = "../data/xml/levels/level1.xml";
    levelXmlPathsSize = 1;
}

Level::~Level()
{
}

// This function will parse through an XML file to construct an array of
// EntityXmlStruct structures
void Level::parse(int level)
{
    TiXmlDocument xmlDoc;

    // Return false if the XML file is not found
    if (!xmlDoc.LoadFile(levelXmlPaths[level].c_str()))
    {
        fprintf(stderr, "[ERROR] parse(): Xml file not found.\n");
        return;
    }

    // The root element of this xml file
    TiXmlElement* rootElement = xmlDoc.RootElement();

    // Parsing the settings element
    TiXmlElement* settings = rootElement->FirstChildElement();
    if (settings == NULL)
    {
        fprintf(stderr, "[ERROR] parse(): settings element not found.\n");
        return;
    }
    levelFinishTime = atoi(settings->Attribute("time"));

    // The parsing EnemyType root element of this xml file
    TiXmlElement* rootEnemyType = settings->NextSiblingElement();
    //if (rootEnemyType->Value() != "EnemyType")
    //{
    //    fprintf(stderr, "[ERROR] parse(): EnemyType root element not found.\n");
    //    return;
    //}

    // Parses through subelements of the EnemyType element and
    // fills data queue and time queue as we go
    for (   TiXmlElement* e = rootEnemyType->FirstChildElement();
            e != NULL;
            e = e->NextSiblingElement())
    {
        timerQueue.push(atoi(e->Attribute("spawn-time")));
        SpawnData data;
        data.x = atoi(e->Attribute("x"));
        data.y = atoi(e->Attribute("y"));
        // Converting c_str to std::string
        const char* cString = e->Attribute("type");
        int cStringSize = strlen(cString);
        data.type.assign(cString, cStringSize);
        dataQueue.push(data);
    }

    int nextSpawnTime = timerQueue.front();
}

void Level::onUpdate()
{
    if (doneLevel)
    {
        if (currentLevel < levelXmlPathsSize)
        {
            timer.stop();
            doneLevel = false;
            parse(currentLevel++);
            timer.start();
        }
        else
        {
            //state transition
            return;
        }
    }

    while (timer.getTimeOnTimer() > nextSpawnTime)
    {
        if (!timerQueue.empty())
        {
            nextSpawnTime = timerQueue.front();
            timerQueue.pop();
            SpawnData toSpawn = dataQueue.front();
            dataQueue.pop();
            spawningQueue.push(toSpawn);
        }
        else
        {
            // Level is done... waiting for level transition
            nextSpawnTime = levelFinishTime+1000;
        }
    }

    if (timer.getTimeOnTimer() > levelFinishTime)
    {
        doneLevel = true;
    }
}

std::queue<SpawnData> Level::getSpawningQueue()
{
    return spawningQueue;
}

SpawnData Level::popSpawningQueue()
{
    SpawnData data = spawningQueue.front();
    spawningQueue.pop();
    return data;
}

void Level::pauseTimers()
{
    timer.pause();
}

void Level::resumeTimers()
{
    timer.resume();
}
