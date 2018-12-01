#include "SiloOrRefinery.h"

#include "Player.h"

SiloOrRefinery::SiloOrRefinery(Player& player, int id, const std::string& name, int health, const Point& size, int capacity) :
Building(player, id, name, health, size), capacity(capacity) {
    player.especiaCapacity += capacity;
}

bool SiloOrRefinery::tryToStoreSome(int& especia) {
    int roomLeft = player.especiaCapacity - player.especia;
    if (especia > roomLeft) {
        especia -= roomLeft;
        player.addEspecia(roomLeft);
        return false;
    }
    player.addEspecia(especia);
    especia = 0;
    return true;
}

SiloOrRefinery::~SiloOrRefinery() {
    player.especiaCapacity -= capacity;
    if (player.especia > player.especiaCapacity) player.especia = player.especiaCapacity;
}