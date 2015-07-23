#include "initialization.h"

//============================================
//CITY INITIALIZATION
//============================================
std::vector<city> init_cities(){
	std::string description = "This is a boring description for the town of Anyd next to the tundra and desert";
	//city template (name, description, x, y, rep, defense, max_soldiers)
	city Anyd("Anyd", description, 369, 614, 15, 10, 4);	//city 1
	description = "This is a boring description for Tullav next to the tundra and forest";
	city Tullav("Tullav", description, 502, 334, 15, 0, 4);	//city 2
	Tullav.change_has_guild();
	description = "This is a boring description for Wrotridge next to the forest and swamp";
	city Wrotridge("Wrotridge", description, 769, 476, 15, 15, 4);	//etc...
	description = "This is a boring description for Cissell, the island city";
	city Cissel("Cissel", description, 715, 826, 15, 0, 4);
	description = "This is a boring description for Adanicus next to the swamp and jungle";
	city Adanicus("Adanicus", description, 977, 742, 15, 0, 4);
	Adanicus.change_has_guild();
	description = "This is a boring description for the town of Repha next to the necrozone and the jungle";
	city Repha("Repha", description, 1140, 487, 15, 0, 4);
	std::vector<city> cities;
	cities.push_back(Anyd);
	cities.push_back(Tullav);
	cities.push_back(Wrotridge);
	cities.push_back(Cissel);
	cities.push_back(Adanicus);
	cities.push_back(Repha);

	//set upgrade names, descriptions, costs, and defensive bonuses
	std::string desc = "Expanding our guild hall to include more living and training space would allow us to accomodate additional members.";
	upgrade capacity(200, 0, "Capacity", desc, 604, 148);
	desc = "An initial investment into local merchants' establishments would yield a higher monthly income from this city each month.";
	upgrade income(300, 0, "Income", desc, 933, 148);
	desc = "Most of our members bring with them skill in tempering and shaping steel already.  Providing this guild hall with a forge would incentivise our members to keep their equipment in top shape. +(num) to slashing and piercing attacks";
	upgrade forges(250, 0, "Forges", desc, 604, 236);
	desc = "Hiring our own physicians to personally care for our members after receiving injuries would drastically reduce the time before our fighters felt fit to pursue new contracts.";
	upgrade apothecary(150, 0, "Apothecary", desc, 933, 236);
	desc = "Murder holes can be carved out of the city walls' towers so that invading monster hordes can be cut down from inside with relatively little risk to the town watch.  I'm sure the city guard would be appreciative of the investment.";
	upgrade murder_holes(200, 50, "Murder Holes", desc, 604, 324);
	desc = "Among the most rudimentary of a castle's defenses, paying townsfolk to dig a moat around the city walls would help to slow down the advance of any monstrous siege party.";
	upgrade moat(400, 100, "Moat", desc, 933, 324);
	desc = "Some of our engineers have recently informed us of a new trap which can be placed in key areas where monsters may approach the city.  These 'mantraps', as they've been called where they originated, should help to skewer a fair portion of an advancing monster group.";
	upgrade mantraps(250, 75, "Mantraps", desc, 604, 412);
	desc = "As horrifying as it sounds, we've witnessed some monsters capable of conjuring magical elements in the form of basic spells.  Having some of our guild wizards place magical barriers on the walls should protect the city watch from incoming spells while they thin them out.";
	upgrade barriers(300, 90, "Magic Barriers", desc, 933, 412);
	desc = "Pitch ditches are rather grisly when used in traditional warfare, but should monsters make it through the gates, they would provide an excellent monster deterrent for the less squeamish.";
	upgrade pitch_ditches(200, 10, "Pitch Ditch", desc, 604, 500);
	desc = "One of our Council of Mages' latest constructs, these immovable sentries can help our soldiers back up the city watch in key areas should monsters breach the outer defenses.";
	upgrade guardian_eyes(400, 20, "Guardian Eyes", desc, 933, 500);

	//assign test upgrades to cities
	for(unsigned int i=0; i<cities.size(); i++){
		cities[i].guild_upgrades.push_back(capacity);
		cities[i].guild_upgrades.push_back(income);
		cities[i].guild_upgrades.push_back(forges);
		cities[i].guild_upgrades.push_back(apothecary);
		cities[i].guild_upgrades.push_back(murder_holes);
		cities[i].guild_upgrades.push_back(moat);
		cities[i].guild_upgrades.push_back(mantraps);
		cities[i].guild_upgrades.push_back(barriers);
		cities[i].guild_upgrades.push_back(pitch_ditches);
		cities[i].guild_upgrades.push_back(guardian_eyes);
	}

	//loop through cities and unlock upgrades for cities with guilds
	for(unsigned int i=0; i<cities.size(); i++){
		if(cities[i].get_has_guild() == true){
			for(unsigned int j=0; j<cities[i].guild_upgrades.size(); j++){
				cities[i].guild_upgrades[j].locked = false;
			}
		}
	}

	return cities;
}

//==================================
//MONSTER INITIALIZATION
//==================================

std::map<std::string, monster> initialize_monster_list(){
	//this map will allow random access lookup of each monster's stats
	//	by name, and will also allow iteration through the entire list
	//  for cancelling and adding purposes
	std::map<std::string, monster> master_monster_list;

//Forest
monster wolf("Wolf", 50, EASY, FOREST);
monster mush_man("Mushroom Monster", 50, EASY, FOREST);
monster centaur("Centaur", 75, MEDIUM, FOREST);
monster g_spider("Giant Spider", 75, MEDIUM, FOREST);
monster centipede("Giant Centipede", 100, HARD, FOREST);
monster treant("Treant", 100, HARD, FOREST);

//Jungle
monster dragonfly("Flyman", 50, EASY, JUNGLE);
monster monkey("White Bug-Monkey", 50, EASY, JUNGLE);
monster plant("Venus Fly Seeker", 75, MEDIUM, JUNGLE);
monster snake("Giant Constrictor", 75, MEDIUM, JUNGLE);
monster panther("Phase Panther", 100, HARD, JUNGLE);
monster gnoll("Gnoll", 100, HARD, JUNGLE);

//Tundra
monster wisp("Will-o'-Wisp", 50, EASY, TUNDRA);
monster iceimp("Ice Imp", 50, EASY, TUNDRA);
monster ielemental("Ice Elemental", 75, MEDIUM, TUNDRA);
monster tiger("Ice Tiger", 75, MEDIUM ,TUNDRA);
monster yeti("Yeti", 100, HARD, TUNDRA);
monster dwarf("Feral Snow Dwarf", 100, HARD, TUNDRA);

//Desert
monster scarab("Scarab", 50, EASY, DESERT);
monster kenku("Desert Bandit Beast", 50, EASY, DESERT);
monster delemental("Dust Elemental", 75, MEDIUM, DESERT);
monster basilisk("Basilisk", 75, MEDIUM, DESERT);
monster golem("Stone Golem", 100, HARD, DESERT);
monster anubis("Royal Anubis", 100, HARD, DESERT);

//Swamp
monster ooze("Ooze", 50, EASY, SWAMP);
monster landshark("Skiver", 50, EASY, SWAMP);
monster lurker("Swamp Lurker", 75, MEDIUM, SWAMP);
monster slug("Demon Slug", 75, MEDIUM, SWAMP);
monster stalker("Muckstalker", 100, HARD, SWAMP);
monster lizard("Lizardman", 100, HARD, SWAMP);

//Necromantically Corrupted Zone
monster skeleton("Skeleton", 50, EASY, NECROZONE);
monster wraith("Wraith", 50, EASY, NECROZONE);
monster raptor("Reanimated Raptor", 75, MEDIUM, NECROZONE);
monster gargoyle("Gargoyle", 75, MEDIUM, NECROZONE);
monster knight("Shadow Knight", 100, HARD, NECROZONE);
monster necromancer("Necromancer", 100, HARD, NECROZONE);

//Coast
monster mudcrab("Mudcrab", 50, EASY, COAST);
monster turtle("Dragon Turtle", 50, EASY, COAST);
monster naga("Naga", 75, MEDIUM, COAST);
monster landsquid("Tidecaller", 75, MEDIUM, COAST);
monster mindflayer("Mindflayer", 100, HARD, COAST);
monster leviathan("Leviathan", 100, HARD, COAST);

//Volcano
monster sprite("Fire Sprite", 50, EASY, VOLCANO);
monster beetle("Fire Beetle", 50, EASY, VOLCANO);
monster felemental("Fire Elemental", 75, MEDIUM, VOLCANO);
monster toad("Lava Toad", 75, MEDIUM, VOLCANO);
monster tank("Lava Rock Tank Monster", 100, HARD, VOLCANO);
monster narwhale("Flying Lava Narwhale", 100, HARD, VOLCANO);

//================================================================================
//FLESHING OUT THE MASTER MONSTER LIST
//================================================================================

master_monster_list.insert(std::pair<std::string, monster>("wolf", wolf));
master_monster_list.insert(std::pair<std::string, monster>("mush_man", mush_man));
master_monster_list.insert(std::pair<std::string, monster>("centaur", centaur));
master_monster_list.insert(std::pair<std::string, monster>("g_spider", g_spider));
master_monster_list.insert(std::pair<std::string, monster>("centipede", centipede));
master_monster_list.insert(std::pair<std::string, monster>("treant", treant));
master_monster_list.insert(std::pair<std::string, monster>("dragonfly", dragonfly));
master_monster_list.insert(std::pair<std::string, monster>("monkey", monkey));
master_monster_list.insert(std::pair<std::string, monster>("plant", plant));
master_monster_list.insert(std::pair<std::string, monster>("snake", snake));
master_monster_list.insert(std::pair<std::string, monster>("panther", panther));
master_monster_list.insert(std::pair<std::string, monster>("gnoll", gnoll));
master_monster_list.insert(std::pair<std::string, monster>("wisp", wisp));
master_monster_list.insert(std::pair<std::string, monster>("iceimp", iceimp));
master_monster_list.insert(std::pair<std::string, monster>("ielemental", ielemental));
master_monster_list.insert(std::pair<std::string, monster>("tiger", tiger));
master_monster_list.insert(std::pair<std::string, monster>("yeti", yeti));
master_monster_list.insert(std::pair<std::string, monster>("dwarf", dwarf));
master_monster_list.insert(std::pair<std::string, monster>("scarab", scarab));
master_monster_list.insert(std::pair<std::string, monster>("kenku", kenku));
master_monster_list.insert(std::pair<std::string, monster>("delemental", delemental));
master_monster_list.insert(std::pair<std::string, monster>("basilisk", basilisk));
master_monster_list.insert(std::pair<std::string, monster>("golem", golem));
master_monster_list.insert(std::pair<std::string, monster>("anubis", anubis));
master_monster_list.insert(std::pair<std::string, monster>("ooze", ooze));
master_monster_list.insert(std::pair<std::string, monster>("landshark", landshark));
master_monster_list.insert(std::pair<std::string, monster>("lurker", lurker));
master_monster_list.insert(std::pair<std::string, monster>("slug", slug));
master_monster_list.insert(std::pair<std::string, monster>("stalker", stalker));
master_monster_list.insert(std::pair<std::string, monster>("lizard", lizard));
master_monster_list.insert(std::pair<std::string, monster>("skeleton", skeleton));
master_monster_list.insert(std::pair<std::string, monster>("wraith", wraith));
master_monster_list.insert(std::pair<std::string, monster>("raptor", raptor));
master_monster_list.insert(std::pair<std::string, monster>("gargoyle", gargoyle));
master_monster_list.insert(std::pair<std::string, monster>("knight", knight));
master_monster_list.insert(std::pair<std::string, monster>("necromancer", necromancer));
master_monster_list.insert(std::pair<std::string, monster>("mudcrab", mudcrab));
master_monster_list.insert(std::pair<std::string, monster>("turtle", turtle));
master_monster_list.insert(std::pair<std::string, monster>("naga", naga));
master_monster_list.insert(std::pair<std::string, monster>("landsquid", landsquid));
master_monster_list.insert(std::pair<std::string, monster>("mindflayer", mindflayer));
master_monster_list.insert(std::pair<std::string, monster>("leviathan", leviathan));
master_monster_list.insert(std::pair<std::string, monster>("sprite", sprite));
master_monster_list.insert(std::pair<std::string, monster>("beetle", beetle));
master_monster_list.insert(std::pair<std::string, monster>("felemental", felemental));
master_monster_list.insert(std::pair<std::string, monster>("toad", toad));
master_monster_list.insert(std::pair<std::string, monster>("tank", tank));
master_monster_list.insert(std::pair<std::string, monster>("narwhale", narwhale));

	return master_monster_list;
}

//====================================
//BATTLESCAPE INITIALIZATION
//====================================

std::map<std::string, battlescape> initialize_battlescape_list(){
	
	std::map<std::string, battlescape> master_battlescape_list;
	
	//forest scapes
	battlescape forest1("forest1", FOREST);
	battlescape forest2("forest2", FOREST);
	battlescape forest3("forest3", FOREST);

	//jungle scapes
	battlescape jungle1("jungle1", JUNGLE);
	battlescape jungle2("jungle2", JUNGLE);
	battlescape jungle3("jungle3", JUNGLE);

	//tundra scapes
	battlescape tundra1("tundra1", TUNDRA);
	battlescape tundra2("tundra2", TUNDRA);
	battlescape tundra3("tundra3", TUNDRA);

	//desert scapes
	battlescape desert1("desert1", DESERT);
	battlescape desert2("desert2", DESERT);
	battlescape desert3("desert3", DESERT);

	//swamp scapes
	battlescape swamp1("swamp1", SWAMP);
	battlescape swamp2("swamp2", SWAMP);
	battlescape swamp3("swamp3", SWAMP);

	//necrozone scapes
	battlescape necrozone1("necrozone1", NECROZONE);
	battlescape necrozone2("necrozone2", NECROZONE);
	battlescape necrozone3("necrozone3", NECROZONE);

	//coast scapes
	battlescape coast1("coast1", COAST);
	battlescape coast2("coast2", COAST);
	battlescape coast3("coast3", COAST);

	//volcano scapes
	battlescape volcano1("volcano1", VOLCANO);
	battlescape volcano2("volcano2", VOLCANO);
	battlescape volcano3("volcano3", VOLCANO);

	//===============================================================
	//FLESHING OUT MASTER BATTLESCAPE LIST
	//===============================================================

	master_battlescape_list.insert(std::pair<std::string, battlescape>("forest1", forest1));
	master_battlescape_list.insert(std::pair<std::string, battlescape>("forest2", forest2));
	master_battlescape_list.insert(std::pair<std::string, battlescape>("forest3", forest3));
	master_battlescape_list.insert(std::pair<std::string, battlescape>("jungle1", jungle1));
	master_battlescape_list.insert(std::pair<std::string, battlescape>("jungle2", jungle2));
	master_battlescape_list.insert(std::pair<std::string, battlescape>("jungle3", jungle3));
	master_battlescape_list.insert(std::pair<std::string, battlescape>("tundra1", tundra1));
	master_battlescape_list.insert(std::pair<std::string, battlescape>("tundra2", tundra2));
	master_battlescape_list.insert(std::pair<std::string, battlescape>("tundra3", tundra3));
	master_battlescape_list.insert(std::pair<std::string, battlescape>("desert1", desert1));
	master_battlescape_list.insert(std::pair<std::string, battlescape>("desert2", desert2));
	master_battlescape_list.insert(std::pair<std::string, battlescape>("desert3", desert3));
	master_battlescape_list.insert(std::pair<std::string, battlescape>("swamp1", swamp1));
	master_battlescape_list.insert(std::pair<std::string, battlescape>("swamp2", swamp2));
	master_battlescape_list.insert(std::pair<std::string, battlescape>("swamp3", swamp3));
	master_battlescape_list.insert(std::pair<std::string, battlescape>("necrozone1", necrozone1));
	master_battlescape_list.insert(std::pair<std::string, battlescape>("necrozone2", necrozone2));
	master_battlescape_list.insert(std::pair<std::string, battlescape>("necrozone3", necrozone3));
	master_battlescape_list.insert(std::pair<std::string, battlescape>("coast1", coast1));
	master_battlescape_list.insert(std::pair<std::string, battlescape>("coast2", coast2));
	master_battlescape_list.insert(std::pair<std::string, battlescape>("coast3", coast3));
	master_battlescape_list.insert(std::pair<std::string, battlescape>("volcano1", volcano1));
	master_battlescape_list.insert(std::pair<std::string, battlescape>("volcano2", volcano2));
	master_battlescape_list.insert(std::pair<std::string, battlescape>("volcano3", volcano3));

	return master_battlescape_list;
}

//============================================================================
//MISSION DESCRIPTION INITIALIZATION
//============================================================================

//============================================================================
//MAJOR NOTE:
/*When customizing mission parameters, if a city is specified but not a biome,
there will be issues.  The generation algorithm defines the biome before the 
city, and it does not know how to assign biomes correctly given only a city.  
If you wish to specify a city for a mission, make sure you make only the biomes
associated with the city to be valid biomes in the mission parameters as well
*/
//============================================================================

std::map<std::string, mission_description> initialize_mission_description_list(const std::map<std::string, monster> &monster_list,
	const std::map<std::string, battlescape> &battlescape_list){

	std::map<std::string, mission_description> master_mission_description_list;

	std::string description;
	battlescape custom("Invalid", VOLCANO);
	
	//=========================================================================
	//MISSION DESCRIPTION INITIALIZATION
	//=========================================================================

	//GENERIC MISSIONS: ANY BIOME, CITY, MONSTER LIST, DIFFICULTY, REWARDS, AND BATTLESCAPE

	description = "A small band of beasts has been spotted in the (biome) around (city).  The town guard has requested professional help in dealing with them.";
	mission_description generic1(description);
	generic1.set_basic_difficulties_valid();
	generic1.make_all_biomes_valid();

	description = "Beasts are roaming the land and devouring villagers near the town of (city).  Assistance is required to combat this menace.";
	mission_description generic2(description);
	generic2.set_basic_difficulties_valid();
	generic2.make_all_biomes_valid();

	description = "(city) has sent a messenger asking for the Sportsmens' aid.  Farmers in and around the (biome) surrounding the city have been disappearing.";
	mission_description generic3(description, NOCITY, -1, 25);
	generic3.set_basic_difficulties_valid();
	generic3.make_all_biomes_valid();

	description = "Travelers on the roads surrounding (city) have reportedly not arrived at their destinations in great numbers.  An investigation should take place.";
	mission_description generic4(description);
	generic4.set_basic_difficulties_valid();
	generic4.make_all_biomes_valid();

	description = "Children have been reported missing by settlers outside (city).  These abductions cannot be left unchecked.";
	mission_description generic5(description);
	generic5.set_basic_difficulties_valid();
	generic5.make_all_biomes_valid();

	description = "Hideous noises have been heard around the (biome) surrounding (city).  No man could make such vile sounds.  This sounds like a job for the Sportsmen!";
	mission_description generic6(description);
	generic6.set_basic_difficulties_valid();
	generic6.make_all_biomes_valid();

	//FOREST MISSIONS: FOREST BIOME ONLY

	description = "Screams have been heard from the woods surrounding (city), from both man and beast.";
	mission_description forestscreams(description);
	forestscreams.set_basic_difficulties_valid();
	forestscreams.make_biome_valid(FOREST);

	description = "Villagers have been found trapped in massive cocoons around (city).  Giant spiders cannot be left to multiply uncontrolled.";
	mission_description forestspiders(description);
	forestspiders.set_difficulty_valid(MEDIUM);
	forestspiders.make_monster_valid(monster_list.find("g_spider")->second);
	custom = battlescape_list.find("forest2")->second;
	forestspiders.set_battlescape(custom);
	
	//JUNGLE MISSIONS: JUNGLE BIOME ONLY

	description = "A cacophony of screeches and wails from the nearby rainforest is keeping the townsfolk of (city) awake at night and fearful for their families.  A party is requested to frighten the beasts into submission.";
	mission_description junglescreams(description);
	junglescreams.set_basic_difficulties_valid();
	junglescreams.make_biome_valid(JUNGLE);

	description = "A villager reports that a screeching creature made off with his livestock into the nearby rainforest canopy.  A creature nimble and strong enough to carry a sheep up a tree presents a serious threat.";
	mission_description junglemonkey(description);
	junglemonkey.set_basic_difficulties_valid();
	junglemonkey.make_biome_valid(JUNGLE);

	//TUNDRA MISSIONS: TUNDRA BIOME ONLY

	description = "Natives of the frozen plains a days walk from (city) have reported sighting a creature they call Umo'Tai in great numbers and hunting closer to the city.  Their description of the beast was fearsom indeed.";
	mission_description tundrayeti(description, NOCITY, 500, 40);
	tundrayeti.make_biome_valid(TUNDRA);
	tundrayeti.set_difficulty_valid(HARD);
	tundrayeti.make_monster_valid(monster_list.find("yeti")->second);

	description = "The icy winds have battered the people of (city) this past Winter, and the Spring has replaced those winds only with hunting beasts leaving hibernation.";
	mission_description tundrawinds(description);
	tundrawinds.make_biome_valid(TUNDRA);
	tundrawinds.set_basic_difficulties_valid();
	tundrawinds.make_monster_invalid(monster_list.find("wisp")->second);

	//DESERT MISSION: DESERT BIOME ONLY

	description = "The sands run red with blood near (city) where hideous creatures have been spotted dragging peasants into the earth.";
	mission_description desertsands(description, CITY2, -1, -1, 15);
	desertsands.set_basic_difficulties_valid();
	desertsands.make_biome_valid(DESERT);
	
	description = "Villagers have spotted small desert creatures herding scarabs and raiding caravans.  Such organizational skills from monsters are of great concern and must be dealt with.";
	mission_description desertbandits(description);
	desertbandits.make_monster_valid(monster_list.find("kenku")->second);
	desertbandits.make_monster_valid(monster_list.find("scarab")->second);
	desertbandits.make_biome_valid(DESERT);
	desertbandits.set_difficulty_valid(EASY);
	desertbandits.set_custom_monster(monster_list.find("scarab")->second);
	desertbandits.set_custom_monster(monster_list.find("kenku")->second);

	//SWAMP MISSIONS: SWAMP BIOME ONLY

	description = "Vile noises are heard from the bogs near (city) at all hours of the day.  (city) dwellers are accustomed to everyday swamp sounds and would not report a minor sleeping disturbance.";
	mission_description swampnoise(description);
	swampnoise.set_basic_difficulties_valid();
	swampnoise.make_biome_valid(SWAMP);

	description = "Fishermen from (city) have been disappearing in the nearby bogs.  Gone are the days when there are no fish big enough to pull a man under in Fairmoor.";
	mission_description swampfish(description);
	swampfish.set_basic_difficulties_valid();
	swampfish.make_biome_valid(SWAMP);

	//NECROZONE MISSIONS: NECROZONE BIOME ONLY

	description = "The dead are restless and are relentlessly harassing the town of (city).  These abominations cannot be left to do as they please.";
	mission_description necrodead(description);
	necrodead.set_basic_difficulties_valid();
	necrodead.make_biome_valid(NECROZONE);

	description = "After the war against necromancy some decades ago, the people of Fairmoor have been relatively safe if they avoid the old battlefields.  This is changing.  Something is agitating the undead, and the Sportsmen have been called to put a stop to it.";
	mission_description necroundead(description);
	necroundead.set_basic_difficulties_valid();
	necroundead.make_biome_valid(NECROZONE);

	//COAST MISSIONS: COAST BIOME ONLY

	description = "Fishing boats are being capsized and children dragged from the beaches near (city).  Rogue waves are not the cause of these disappearances.";
	mission_description coastwaves(description);
	coastwaves.set_basic_difficulties_valid();
	coastwaves.make_biome_valid(COAST);

	description = "Citizens of (city) fear their once safest travelling paths along the rocky coast of southern Fairmoor.  Restore peace to the beaches, and put the road raiders in their place.";
	mission_description coastroad(description);
	coastroad.set_basic_difficulties_valid();
	coastroad.make_biome_valid(COAST);

	//VOLCANO MISSIONS: VOLCANO BIOME ONLY


	//CITY SPECIFIC MISSIONS: THE CITY OF THE MISSION IS ALREADY SPECFIED

	description = "Citizens of Anyd recently hosted a hunting tournament of their own.  When several of the competitors were eaten, they realized they weren't just dealing with bears.  They've requested the Sportsmens' assistance.";
	mission_description city1(description, CITY1);
	city1.set_basic_difficulties_valid();
	city1.make_biome_valid(DESERT);
	city1.make_biome_valid(TUNDRA);

	description = "Tullav is famous for its exquisite trade goods despite its limited resources, but trade routes have been recently raided by monsters to the point that no one else in Fairmoor will risk the journey to bring them business.  The city needs help.";
	mission_description city2(description, CITY2);
	city2.set_basic_difficulties_valid();
	city2.make_biome_valid(TUNDRA);
	city2.make_biome_valid(FOREST);

	description = "The town watch of Wrotridge has received numerous reports from a small nearby farming community about increased aggression from the local fauna.  The watch is spread thin as it is and is asking the Sportsmen to lend their aid.";
	mission_description city3(description, CITY3);
	city3.set_basic_difficulties_valid();
	city3.make_biome_valid(FOREST);
	city3.make_biome_valid(SWAMP);

	description = "Villagers from (city) have reported sightings of more docile wildlife being mauled and killed for sport.  There is no place for senseless killing in Fairmoor.";
	mission_description city4(description, CITY4);
	city4.set_basic_difficulties_valid();
	city4.make_biome_valid(COAST);
	city4.make_biome_valid(DESERT);

	description = "Foot traffic to and from the city of (city) has all but ceased in recent months.  Neighboring cities suspect someone or something is controlling the roads.  No doubt (city) would be grateful for intervention.";
	mission_description city5(description, CITY5);
	city5.set_basic_difficulties_valid();
	city5.make_biome_valid(JUNGLE);
	city5.make_biome_valid(SWAMP);

	description = "Repha, known as one of the more jovial cities of Fairmoor, has suffered a severe drop in festivities due to an increasing number of deaths from beast attacks.  Restore the good mood of Repha, Sportsmen.";
	mission_description city6(description, CITY6);
	city6.set_basic_difficulties_valid();
	city6.make_biome_valid(JUNGLE);
	city6.make_biome_valid(NECROZONE);

	
	master_mission_description_list.insert(std::pair<std::string, mission_description>("generic1", generic1));
	master_mission_description_list.insert(std::pair<std::string, mission_description>("generic2", generic2));
	master_mission_description_list.insert(std::pair<std::string, mission_description>("generic3", generic3));
	master_mission_description_list.insert(std::pair<std::string, mission_description>("generic4", generic4));
	master_mission_description_list.insert(std::pair<std::string, mission_description>("generic5", generic5));
	master_mission_description_list.insert(std::pair<std::string, mission_description>("generic6", generic6));
	master_mission_description_list.insert(std::pair<std::string, mission_description>("forest1", forestscreams));
	master_mission_description_list.insert(std::pair<std::string, mission_description>("forest2", forestspiders));
	master_mission_description_list.insert(std::pair<std::string, mission_description>("jungle1", junglescreams));
	master_mission_description_list.insert(std::pair<std::string, mission_description>("jungle2", junglemonkey));
	master_mission_description_list.insert(std::pair<std::string, mission_description>("tundra1", tundrayeti));
	master_mission_description_list.insert(std::pair<std::string, mission_description>("tundra2", tundrawinds));
	master_mission_description_list.insert(std::pair<std::string, mission_description>("desert1", desertsands));
	master_mission_description_list.insert(std::pair<std::string, mission_description>("desert2", desertbandits));
	master_mission_description_list.insert(std::pair<std::string, mission_description>("swamp1", swampnoise));
	master_mission_description_list.insert(std::pair<std::string, mission_description>("swamp2", swampfish));
	master_mission_description_list.insert(std::pair<std::string, mission_description>("necrozone1", necrodead));
	master_mission_description_list.insert(std::pair<std::string, mission_description>("necrozone2", necroundead));
	master_mission_description_list.insert(std::pair<std::string, mission_description>("coast1", coastwaves));
	master_mission_description_list.insert(std::pair<std::string, mission_description>("coast2", coastroad));
	master_mission_description_list.insert(std::pair<std::string, mission_description>("city1", city1));
	master_mission_description_list.insert(std::pair<std::string, mission_description>("city2", city2));
	master_mission_description_list.insert(std::pair<std::string, mission_description>("city3", city3));
	master_mission_description_list.insert(std::pair<std::string, mission_description>("city4", city4));
	master_mission_description_list.insert(std::pair<std::string, mission_description>("city5", city5));
	master_mission_description_list.insert(std::pair<std::string, mission_description>("city6", city6));

	return master_mission_description_list;

}

//==================================================================================
//STORY MISSION MASTER LIST INITIALIZATION
//==================================================================================

std::vector<mission_description> initialize_master_story_mission_list(const std::map<std::string, monster> &monster_list,
	const std::map<std::string, battlescape> &battlescape_list){

	std::vector<mission_description>  story_mission_description_list;

	//initialize monster and battlescape lists
	//std::map<std::string, monster> monster_list = initialize_monster_list();
	//std::map<std::string, battlescape> battlescape_list = initialize_battlescape_list();

	std::string description;

	description = "In order to establish yourself in Fairmoor, you might find it useful to do some pro-bono work with a city favorable for the guild's expansion.  Doing work for a city without them having to pay you would greatly increase your reputation with them.";
	mission_description story1(description, NOCITY, -1, -1, 1, -1, 2);
	story1.set_difficulty_valid(EASY);
	story1.make_biome_valid(FOREST);

	description = "The King has lost a large shipment of gold along the (biome) roads near (city).  He has promised a significant portion should we manage to find out what happenned to his majesty's escort.";
	mission_description story2(description, NOCITY, -1, -1, 1, -1, 3);
	story2.set_basic_difficulties_valid();
	story2.make_all_biomes_valid();

	description = "The Lord of (city) has mysteriously lost several relatives around the (biome) near his vacation home.  There was no sign of death, and beasts are not known for taking prisoners.  This news is most perturbing to him, and he is seeking professional help in the investigation.";
	mission_description story3(description, NOCITY, -1, -1, 1, -1, 4);
	story3.set_basic_difficulties_valid();
	story3.make_all_biomes_valid();

	story_mission_description_list.push_back(story1);
	story_mission_description_list.push_back(story2);
	story_mission_description_list.push_back(story3);

	return story_mission_description_list;
}

//============================================================================
//INITIALIZATION OF CITIES BY BIOME
//============================================================================

void initialize_cities_by_biome(std::vector<std::vector<CITY>> &cities_by_biome){
	cities_by_biome.resize(7);

	//the forest biome is adjacent to cities 2 and 3
	cities_by_biome[FOREST].push_back(CITY2);
	cities_by_biome[FOREST].push_back(CITY3);

	//the desert biome is adjacent to cities 1 and 4
	cities_by_biome[DESERT].push_back(CITY4);
	cities_by_biome[DESERT].push_back(CITY1);

	//the tundra biome is adjacent to cities 1 and 2
	cities_by_biome[TUNDRA].push_back(CITY1);
	cities_by_biome[TUNDRA].push_back(CITY2);

	//the coast biome is adjacent to city 4
	cities_by_biome[COAST].push_back(CITY4);

	//the swamp biome is adjacent to cities 3 and 5
	cities_by_biome[SWAMP].push_back(CITY3);
	cities_by_biome[SWAMP].push_back(CITY5);

	//the jungle biome is adjacent to cities 5 and 6
	cities_by_biome[JUNGLE].push_back(CITY5);
	cities_by_biome[JUNGLE].push_back(CITY6);

	//the necrozone biome is adjacent to city 6
	cities_by_biome[NECROZONE].push_back(CITY6);
}
