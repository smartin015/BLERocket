#include "ship.h"
#include <cmath>

game::ShipPartT generatePart(uint8_t user, uint16_t score) {
  game::ShipPartT part;
  part.creator = user;

  // We increase the user's part quality
  // based on their closeness to the Phase 1 max score
  float quality = (float(PART_MAX_QUALITY) / float(MAX_SCORE)) * score;
  part.quality = std::max(PART_MIN_QUALITY, std::min(PART_MAX_QUALITY, (uint8_t) std::round(quality)));

  // We use a modulo of the user's ID to determine
  // what part they're able to make.
  // This ensures roughly equal distribution
  // of parts.
  part.type = (game::ShipPartType) (part.creator % (game::ShipPartType_MAX - game::ShipPartType_MIN) + 1);

  return part;
}

int getShipLaunchScore(const game::ShipT& ship) {
  // Sum all ship part scores, with a multiplier
  int acc = 0;
  for (int i = 0; i < ship.parts.size(); i++) {
    acc += ship.parts[i]->quality;
  }
  return acc * SHIP_LAUNCH_SCORE_MULT;
}

#define NUM_SHIP_NAMES 395
// These name come from https://www.fantasynamegenerators.com/spaceship-names.php
static const char SHIP_NAMES[NUM_SHIP_NAMES][MAX_SHIP_NAME_LEN+1] = {
  "Fade", "Mace", "Yucatan", "Intrepid", "Thor", "Meteor", "Teresa", "Victory",
  "Remus", "Sparta", "Merkava", "Alto", "Oblivion", "Europa", "Carnage", "Amazon",
  "Thanatos", "Basilisk", "Isabella", "Totale", "Fafnir", "Scorpio", "Armada", "Pinnacle",
  "Zion", "Aurora", "Apollo", "Loki", "Glorious", "Big Boy", "Artemis", "Rampart", "Deonida",
  "Valhala", "Raven", "Ares", "Huntress", "Siberia", "Striker", "Prennia", "Imperial", "Liberty",
  "Dagger", "Marchana", "Nineveh", "Phoenix", "Death", "Wildcat", "Vigilant", "Arden", "Bravery",
  "Sparrow", "Bob", "Marauder", "Covenant", "Tyrant", "Berserk", "Zephyr", "Vampire", "Promise",
  "Neutron", "Valor", "Sunder", "Fortune", "Aquila", "Zeus", "Desire", "Vulture", "Siren",
  "Calypso", "Vespira", "Ramses", "Avius", "Hunter", "Ulysses", "Pyrrhus", "Dart", "Panama",
  "Diplomat", "Lavanda", "Vagabond", "Celestis", "Bayonet", "Emissary", "Alice", "Angelica", "Cain",
  "Muriela", "Karnack", "Hercules", "Malta", "Herminia", "Praetor", "Piranha", "Zenith", "Matador",
  "Herald", "Genesis", "Phobos", "Britain", "Suzanna", "Lucidity", "Unicorn", "Trenxal", "Maria",
  "Freedom", "Patriot", "Claymore", "Rhodes", "Aries", "Behemoth", "Ohio", "Thunder", "Sara",
  "Detector", "Kipper", "Oberon", "Oregon", "Halo", "Bishop", "Ravana", "Bandit", "Seleucia",
  "Eagle", "Perilous", "Cydonia", "Griffin", "Rising", "Romulus", "Beluga", "Luisa", "Valhalla",
  "Spectrum", "Escorial", "Tenacity", "Kraken", "Cyclone", "Nemesis", "Triumph", "Stalker", "Trinity",
  "Calamity", "Observer", "Guard", "Horizon", "Endeavor", "Blade", "Blossom", "Harmony", "Scythe",
  "Dark", "Invader", "Arcadia", "Analyzer", "Raving", "Explorer", "Executor", "Paradise", "Scimitar",
  "Helios", "Buzzard", "Niagara", "Infinity", "Warrior", "Ravager", "Deimos", "Athens", "Sonne", "Saber",
  "Templar", "Pioneer", "Visitor", "Javelin", "Neptune", "Fudgy", "Antioch", "Pursuer", "Empress",
  "Comet", "Strike", "Clap", "Syracuse", "Ark", "Colossus", "Eternal", "Baldrin", "Shirley",
  "Ripper", "Patience", "Gremlin", "Titan", "Goliath", "Lucky", "Nihilus", "Eternity", "Argonaut",
  "Shade", "Guardian", "Trident", "Legacy", "Nirvana", "Coyote", "Ambition", "Ninja", "Troy",
  "Badger", "Spider", "Ashaton", "Amanda", "Adder", "Irmanda", "Immortal", "Valiant", "Orion",
  "Celina", "Galatea", "Innuendo", "Tourist", "Judgment", "Defiant", "Frontier", "Normandy", "Vanguard",
  "Kennedy", "Titania", "Elena", "Tortoise", "Carthage", "Falcon", "Verminus", "Cordoba", "Phobetor",
  "Viper", "Unity", "Pursuit", "Arcadian", "Leo", "Duke", "Babylon", "Pegasus", "Pandora",
  "Lupus", "Dream", "Atlas", "Poseidon", "Exarch", "Inferno", "Angel", "New Hope", "Typhoon",
  "Spitfire", "Elysium", "Marduk", "Gladius", "Venom", "Courage", "Samurai", "Verdant", "Nuria",
  "Plaiedes", "Silent", "Rhapsody", "Terigon", "Memphis", "Memory", "Avadora", "Archmage", "Tomahawk",
  "Peacock", "Sandra", "Vision", "Infineon", "Elba", "Pontiac", "Reliant", "Ghunne", "Warlock",
  "Hannibal", "Avalon", "Cyclopse", "Thebes", "Anna", "Cloud", "Victoria", "Bastion", "Vera",
  "Wisdom", "Saratoga", "Wyvern", "Seraphim", "Serenity", "Majestic", "Lullaby", "Destiny", "Ural",
  "Icarus", "Geisha", "Kyozist", "Intruder", "Khan", "Euphoria", "Arizona", "Myrmidon", "Paladin",
  "Storm", "Achilles", "Barbara", "Minotuar", "Reaver", "Damascus", "Stalwart", "Nomad", "Crusher",
  "Night", "Proximo", "Chimera", "Arthas", "Slayer", "Argo", "Repulse", "Facade", "Polaris",
  "Anarchy", "Nero", "Watcher", "Starfall", "Dakota", "Wolf", "Nexus", "Omen", "Hope",
  "Rafaela", "Renault", "Chronos", "Gauntlet", "Beholder", "Flavia", "Boa", "Pilgrim", "Avenger",
  "Knossos", "Traveler", "Revenant", "Actium", "Royal", "Crack", "Olavia", "Pelican", "Midway",
  "Frenzy", "Xerxes", "Utopia", "Harpy", "Cyclops", "Corsair", "Burn", "Cossack", "Prophet",
  "Torment", "Serpent", "Lion", "Rascal", "Voyager", "Crash", "Condor", "Karma", "Fate",
  "Twilight", "Cromwell", "Defiance", "Invictus", "Hawk", "Termite", "Virginia", "Hammer", "Despot",
  "Phalanx", "Valkyrie"
};

std::string generateShipName(const game::ShipT& ship) {
  // Start with true random; make fancier later
  return SHIP_NAMES[std::rand() % NUM_SHIP_NAMES];
}
