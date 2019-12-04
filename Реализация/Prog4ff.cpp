#include <iostream>
#include "..\..\Prog4\Prog4\Prog4h.h"
namespace Prog4 {

	const char* msgs1[] = { "0. Quit", "1. Add object", "2. Reset size", "3. Select object", "4. Print"};
	const int NMsgs1 = sizeof(msgs1) / sizeof(msgs1[0]);
	const char* msgs_cell[] = { "0. Quit or select other object", "1. Print type", "2. Print cordinate"};
	const int NMsgs_cell = sizeof(msgs_cell) / sizeof(msgs_cell[0]);
	const char* msgs_platform[] = { "0. Quit or select other object", "1. Print type of cell", "2. Print cordinate", "3. Print type of platform", "4. Add module" ,"5. Find module", "6. Delete module", "7. Select module", "8. Move (only for mobile)" };
	const int NMsgs_platform = sizeof(msgs_platform) / sizeof(msgs_platform[0]);
	const char* msgs_enemy[] = { "0. Quit or select other object", "1. Print type", "2. Print cordinate", "3. Move", "4. Destroy" };
	const int NMsgs_enemy = sizeof(msgs_enemy) / sizeof(msgs_enemy[0]);

	int getNum(int& a)
	{
		std::cin >> a;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore();
			return -1;
		}
		std::cin.clear();
		std::cin.ignore();
		return 1;
	}

	Cordinate input_c() {
		int x, y;
		std::cout << "Input X-cordinate" << std::endl;
		while (getNum(x) < 0 || x < 0)
		{
			std::cout << "You're wrong. Repeat please" << std::endl;
		}
		std::cout << "Input Y-cordinate" << std::endl;
		while (getNum(y) < 0 || y < 0)
		{
			std::cout << "You're wrong. Repeat please" << std::endl;
		}
		return {x,y};
	}

	void input_module_properties(int& mt, int&les, int& lec, int&n, int& nms, int& r) {
		std::cout << "Input type of module" << std::endl;
		while (getNum(mt) < 0 || mt < 0)
		{
			std::cout << "You're wrong. Repeat please" << std::endl;
		}
		std::cout << "Input level of energy supply" << std::endl;
		while (getNum(les) < 0 || les < 0)
		{
			std::cout << "You're wrong. Repeat please" << std::endl;
		}
		std::cout << "Input radius" << std::endl;
		while (getNum(r) < 0 || r < 0)
		{
			std::cout << "You're wrong. Repeat please" << std::endl;
		}
		std::cout << "Input level energy consumption" << std::endl;
		while (getNum(lec) < 0 || lec < 0)
		{
			std::cout << "You're wrong. Repeat please" << std::endl;
		}
		std::cout << "Imput how many slots module takes" << std::endl;
		while (getNum(n) < 0 || n < 0)
		{
			std::cout << "You're wrong. Repeat please" << std::endl;
		}
		std::cout << "Imput max count of session" << std::endl;
		while (getNum(nms) < 0 || nms < 0)
		{
			std::cout << "You're wrong. Repeat please" << std::endl;
		}
	}

	int dialog(const char* msgs[], int N)
	{
		const char* errmsg = "";
		int i, n = 0;
		do {
			puts(errmsg);
			errmsg = "You're wrong. Repeat, please!";
			for (i = 0; i < N; ++i)
				puts(msgs[i]);
			puts("Make our choice: ");
			getNum(n);
		} while (n < 0 || n >= N);
		return n;
	}

	Space::Space() {
		Cordinate c;
		c.x = 10;
		c.y = 10;
		set_Size(c);
		field = new Cell * *[c.x];
		for (int i = 0; i < c.x; i++) {
			field[i] = new Cell * [c.y];
		}
		for (int i = 0; i < c.x; i++)
			for (int j = 0; j < c.x; j++) {
				field[i][j] = new Cell;
				field[i][j]->C.x = i;
				field[i][j]->C.y = j;
			}
	}

	Space::Space(Cordinate c) {
		set_Size(c);
		field = new Cell ** [c.x];
		for (int i = 0; i < c.x; i++) {
			field[i] = new Cell*[c.y];
		}
		for (int i = 0; i < c.x; i++)
			for (int j = 0; j < c.y; j++) {
				field[i][j] = new Cell;
				field[i][j]->C.x = i;
				field[i][j]->C.y = j;
			}
	}

	void Space::set_Size(Cordinate c) {
		Size.x = c.x;
		Size.y = c.y;
	}

	void Space::reset_Size(Cordinate c) {
		if (field != nullptr) {
			Cell*** field2 = new Cell * *[c.x];
			for (int i = 0; i < c.x; i++) {
				field2[i] = new Cell * [c.y];
			}
			for (int i = 0; i < c.x; i++) {
				for (int j = 0; j < c.y; j++) {
					field2[i][j] = new Cell;
					if (i < Size.x && j < Size.y) {
						field2[i][j] = field[i][j];
					}	
					//delete field[i][j];
				}
				//delete field[i];
			}
			//delete field;
			field = field2;
			Size = c;
		}
	}

	int Space::add_object(int type, Cordinate c, int ind, int v, int les, int ns) {
		if (field[c.x][c.y]->get_type() != 0)
			if (ind != 1)
				return 1;
		if (type == 0)
			field[c.x][c.y] = new Cell(c, 0);
		if (type == 1)
			field[c.x][c.y] = new Barrier(c);
		if (type == 2)
			field[c.x][c.y] = new Static_Platform(c, les, ns);
		if (type == 3)
			field[c.x][c.y] = new Mobile_Platform(c, les, ns, v);
		if (type == 4)
			field[c.x][c.y] = new Enemy(c);
		return 0;
	}

	std::ostream& Space::print(std::ostream& s) const {
		for (int j = Size.y - 1; j >= 0; j--) {
			//s << i << " ";
			for (int i = 0; i < Size.x; i++) {
				if (field[i][j]->get_type() == 0)
					s << " .";
				if (field[i][j]->get_type() == 1)
					s << " B";
				if (field[i][j]->get_type() == 2) {
					Platform* platform = dynamic_cast<Platform*>(field[i][j]);
					if (platform->get_pltype() == 1) {
						s << " S";
					}
					else {
						s << " M";
					}
				}
				if (field[i][j]->get_type() == 3)
					s << " E";
			}
			s << std::endl;
		}
		s << "   ";
		//for (int j = 0; j < Size.y; j++)
			//s << j << " ";
		s << std::endl << std::endl;
		return s;
	}

	Space::~Space() {
		for (int i = 0; i < Size.x; i++) {
			for (int j = 0; j < Size.y; j++) {
				delete[] field[i][j];
			}
			delete[] field[i];
		}
		delete[] field;
	}

	Cell::Cell() {
		type = 0;
		C.x = 0;
		C.y = 0;
	}

	Cell::Cell(Cordinate c, int t) {
		type = t;
		C.x = c.x;
		C.y = c.y;
	}

	void Enemy::destruction() {
		Cell* cell = this;
		Enemy* enemy;
		enemy = dynamic_cast<Enemy*>(cell);
		delete enemy;
		type = 0;
	}

	Barrier::Barrier() :Cell({ 0,0 }, 1) {
	}

	Barrier::Barrier(Cordinate c) :Cell(c, 1) {
	}

	Platform::Platform() :Cell({0,0}, 2) {
		pltype = 1;
		strcpy(description, "Empty platform");
		p_level_energy_supply = 100;
		n_slots = 10;
		n_slots_taked = 0;
		//mods = nullptr;
		/*enemies = nullptr;
		barriers = nullptr;
		platforms = nullptr;*/
	}

	Platform::Platform(Cordinate c, int les, int ns) :Cell(c, 2) {
		pltype = 1;
		strcpy(description, "Empty platform");
		p_level_energy_supply = les;
		n_slots = ns;
		n_slots_taked = 0;
		//mods = nullptr;
		/*enemies = nullptr;
		barriers = nullptr;
		platforms = nullptr;*/
	}

	Cordinate Platform::get_module_is(int mt, int les, int lec, int n, int nms, int r) {
		for (int i = 0; i < mods.size(); i++) {
			if (mods[i]->get_mtype() == mt) {
				if (mods[i]->get_level_energy_supply() == les && mods[i]->get_level_energy_cons() == lec && mods[i]->get_n_slots_take() == n && mods[i]->get_R() == r) {
					if (mt == 1) {
						Network* pl = dynamic_cast<Network*>(mods[i]);
						if (pl->get_n_max_session() == nms) {
							return { 1 , i };
						}
					}
				}
			}
		}
		return { -1 , -1 };
	}

	int Platform::add_module(int mt, int les, int lec, bool p, int n, int nms, int r) {
		//if (mods = nullptr) {
		//	mods = new Module*;
		//	*mods = new Module;
		//}
		//else {
		//	Module** mods2 = new Module*[sizeof(mods) / sizeof(Module)];
		//	for (int i = 0; i < sizeof(mods) / sizeof(Module); i++) {
		//		mods2[i] = new Module;
		//	}
		//	for (int i = 0; i < sizeof(mods) / sizeof(Module); i++) {
		//		Module m = *mods[i];///////////////////////////////////////////////
		//		*mods2[i] = m;
		//		delete mods[i];
		//	}
		//	delete mods;
		//	mods = new Module*[sizeof(mods2) / sizeof(Module) + 1];
		//	for (int i = 0; i < sizeof(mods) / sizeof(Module) + 1; i++) {
		//		mods[i] = new Module;
		//	}
		//	for (int i = 0; i < sizeof(mods2) / sizeof(Module); i++) {
		//		*mods[i] = *mods2[i];
		//		delete mods2[i];
		//	}
		//	delete mods2;
		//}
		if (n_slots_taked + n > n_slots)
			return 0;
		if (mt == 1)
			mods.push_back(&Network(les, lec, p, n, nms, r, mods.size()));
			//*mods[sizeof(mods) / sizeof(Module)] = Network();
		if (mt == 2)
			mods.push_back(&Sensor(mt, r, les, lec, p, n, mods.size()));
			//*mods[sizeof(mods) / sizeof(Module)] = Sensor();
		if (mt == 3)
			mods.push_back(&Weapon(mt, les, lec, p, n, r, mods.size()));
		n_slots_taked += n;
		return 1;
			//*mods[sizeof(mods) / sizeof(Module)] = Weapon();
	//	n_mods++;
	}

	int Platform::delete_module(int mt, int les, int lec, int n, int nms, int r) {
		std::vector<Module*>::iterator iter;
		iter = mods.begin();
		int i = get_module_is(mt, les, lec, n, nms, r).y;
		n_slots_taked -= mods[i]->get_n_slots_take();
		if (i) {
			mods.erase(iter + i);
		}
		else
			return 0;
		return 1;
	}
	
		



		//if (mods != nullptr) {
		//	Module** mods2 = new Module * [sizeof(mods) / sizeof(Module)];
		//	for (int i = 0; i < sizeof(mods) / sizeof(Module); i++) {
		//		mods2[i] = new Module;
		//	}
		//	for (int i = 0; i < sizeof(mods) / sizeof(Module); i++) {
		//		Module m = *mods[i];
		//		*mods2[i] = m;
		//		delete mods[i];
		//	}
		//	delete mods;
		//	int x = sizeof(mods2) / sizeof(Module) - 1;
		//	if (x > 0) {
		//		mods = new Module * [x];
		//		for (int i = 0; i < x; i++) {
		//			mods[i] = new Module;
		//		}
		//		for (int i = 0, j = 0; i < x, j < x; i++, j++) {
		//			if (i != t) {
		//				*mods[i] = *mods2[j];
		//				delete mods2[i];
		//			}
		//			else {
		//				i--;
		//			}
		//		}
		//	}
		//	delete mods2;
		//	n_mods--;
		//}

	Enemy::Enemy() :Cell({ 0,0 }, 3) {}

	Enemy::Enemy(Cordinate c) :Cell(c, 3) {}

	Enemy* Enemy::move(int k, Space &S) {
		Enemy* enemy = nullptr;
		if (k == 6 && C.x < S.Size.x - 1)
			if (S.field[C.x + 1][C.y]->get_type() == 0) {
				delete S.field[C.x + 1][C.y];
				S.field[C.x + 1][C.y] = this;
				S.field[C.x][C.y] = new Cell(C, 0);
				enemy = dynamic_cast<Enemy*>(S.field[C.x + 1][C.y]);
				C.x++;
			}
		if (k == 8 && C.y < S.Size.y - 1)
			if (S.field[C.x][C.y + 1]->get_type() == 0) {
				delete S.field[C.x][C.y + 1];
				S.field[C.x][C.y + 1] = this;
				enemy = dynamic_cast<Enemy*>(S.field[C.x][C.y + 1]);
				S.field[C.x][C.y] = new Cell(C, 0);
				C.y++;
			}
		if (k == 4 && C.x > 0)
			if (S.field[C.x - 1][C.y]->get_type() == 0) {
				delete S.field[C.x - 1][C.y];
				S.field[C.x - 1][C.y] = this;
				S.field[C.x][C.y] = new Cell(C, 0);
				enemy = dynamic_cast<Enemy*>(S.field[C.x - 1][C.y]);
				C.x--;
			}
		if (k == 2 && C.y > 0)
			if (S.field[C.x][C.y - 1]->get_type() == 0) {
				delete S.field[C.x][C.y - 1];
				S.field[C.x][C.y - 1] = this;
				S.field[C.x][C.y] = new Cell(C, 0);
				enemy = dynamic_cast<Enemy*>(S.field[C.x][C.y - 1]);
				C.y--;
			}
		return enemy;
	}

	Static_Platform::Static_Platform() :Platform({0,0}, 100, 10) {
		pltype = 1;
		strcpy(description, "Empty static platform");
	}

	Static_Platform::Static_Platform(Cordinate c, int les, int ns) : Platform(c, les, ns) {
		pltype = 1;
		strcpy(description, "Empty static platform");
		/*mods = nullptr;
		enemies = nullptr;
		barriers = nullptr;
		platforms = nullptr;*/
	}

	Static_Platform::~Static_Platform() {
		mods.clear();
		enemies.clear();
		barriers.clear();
		platforms.clear();
	}

	Mobile_Platform::Mobile_Platform() :Platform({ 0,0 }, 100, 10) {
		pltype = 2;
		V = 1;
		strcpy(description, "Empty mobile platform");
	}

	Mobile_Platform::Mobile_Platform(Cordinate c, int les, int ns, int v) : Platform(c, les, ns) {
		pltype = 2;
		V = v;
		strcpy(description, "Empty mobile platform");
		/*mods = nullptr;
		enemies = nullptr;
		barriers = nullptr;
		platforms = nullptr;*/
	}


	Mobile_Platform* Mobile_Platform::Move(int k, Space &S) {
		Mobile_Platform* mp = nullptr;
		if (k == 6 && C.x < S.Size.x - 1)
			if (S.field[C.x + 1][C.y]->get_type() == 0) {
				delete S.field[C.x + 1][C.y];
				S.field[C.x + 1][C.y] = this;
				S.field[C.x][C.y] = new Cell(C, 0);
				mp = dynamic_cast<Mobile_Platform*>(S.field[C.x + 1][C.y]);
				C.x++;
			}
		if (k == 8 && C.y < S.Size.y - 1)
			if (S.field[C.x][C.y + 1]->get_type() == 0) {
				delete S.field[C.x][C.y + 1];
				S.field[C.x][C.y + 1] = this;
				mp = dynamic_cast<Mobile_Platform*>(S.field[C.x][C.y + 1]);
				S.field[C.x][C.y] = new Cell(C, 0);
				C.y++;
			}
		if (k == 4 && C.x > 0)
			if (S.field[C.x - 1][C.y]->get_type() == 0) {
				delete S.field[C.x - 1][C.y];
				S.field[C.x - 1][C.y] = this;
				S.field[C.x][C.y] = new Cell(C, 0);
				mp = dynamic_cast<Mobile_Platform*>(S.field[C.x - 1][C.y]);
				C.x--;
			}
		if (k == 2 && C.y > 0)
			if (S.field[C.x][C.y - 1]->get_type() == 0) {
				delete S.field[C.x][C.y - 1];
				S.field[C.x][C.y - 1] = this;
				S.field[C.x][C.y] = new Cell(C, 0);
				mp = dynamic_cast<Mobile_Platform*>(S.field[C.x][C.y - 1]);
				C.y--;
			}
		return mp;
	}

	Mobile_Platform::~Mobile_Platform() {
		mods.clear();
		enemies.clear();
		barriers.clear();
		platforms.clear();
	}

	Module::Module() {
		R = 5;
		mtype = 0;
		level_energy_supply = 100;
		level_energy_cons = 1;
		power = true;
		n_slots_take = 1;
	}

	Module::Module(int les, int lec, bool p, int n, int r) {
		R = r;
		mtype = 0;
		level_energy_supply = les;
		level_energy_cons = lec;
		power = p;
		n_slots_take = n;
	}

	Network::Network() :Module(100, 1, true, 1, 5) {
		i = 0;
		mtype = 1;
		session = 0;
		n_max_session = 100;
		//n_active = 0;
		//n_all = 0;
		//active = nullptr;
		//all = nullptr;
	}

	Network::Network(int les, int lec, bool p, int n, int nms, int r, int j) :Module(les, lec, p, n, r) {
		i = j;
		mtype = 1;
		n_max_session = nms;
		session = 0;
		//n_active = 0;
		//n_all = 0;
		/*active = nullptr;
		all = nullptr;*/
	}

	//void Network::get_Partners(Space &S, Platform &P) {
	//	active.clear();
	//	for (int i = 0; i < 2 * R; i++) {
	//		for (int j = 0; j < 2 * R; j++) {
	//			if (P.C.x - R + i >= 0 && P.C.y - R + j >= 0)
	//				if ((((P.C.x - R + i) - P.C.x) * ((P.C.x - R + i) - P.C.x) + ((P.C.y - R + j) - P.C.y) * ((P.C.y - R + j) - P.C.y)) <= (R + Sq) * (R + Sq)) {
	//					if (S.field[P.C.x - R + i][P.C.y - R + j]->get_type() == 2) {
	//						Cell* cell = S.field[P.C.x - R + i][P.C.y - R + j];
	//						Static_Platform* platform;
	//						platform = dynamic_cast<Static_Platform*>(cell);
	//						//Network* network_module;
	//						if (platform->get_module_is(1).x == 1) {
	//							set_Connection(P.C, { P.C.x - R + i, P.C.y - R + j });
	//							all.push_back(platform);
	//							active.push_back(platform);

	//							/*Module* module = platform->mods[platform->get_module_is(1).y];
	//							network_module = dynamic_cast<Network*>(module);
	//							all[n_all] = network_module;*/
	//						
	//						}
	//					}
	//				}
	//		}
	//	}
	//}

	void Network::set_Connection(Cordinate c1, Cordinate c2) {
		std::cout << "[" << c1.x << " , " << c1.y << "] - [" << c2.x << " , " << c2.y << "] : " << "Connection sucsess!";
	}


	std::vector<Platform*> Network::give_Partners() {
		return active;
	}

	/*void Network::ask_Partners(Cordinate c, Space &S, Platform &P) {
		Static_Platform* platform = new Static_Platform;
		if (S.field[P.C.x][P.C.y]->get_type() == 2) {
			Cell* cell = S.field[P.C.x][P.C.y];
			platform = dynamic_cast<Static_Platform*>(cell);
		}
		Network* network_module;
		if (platform->get_module_is(1).x == 1) {
			Module* module = platform->mods[platform->get_module_is(1).y];
			network_module = dynamic_cast<Network*>(module);
			for (int i = 0; i < network_module->give_Partners().size(); i++) {
				all.push_back(network_module->give_Partners()[i]);
				active.push_back(network_module->give_Partners()[i]);
			}
		}
	}*/

	void Network::take_info(Platform &P) {
		for (int i = 0; i < active.size(); i++) {
			for (int j = 0; j< active[i]->barriers.size(); j++)
				P.barriers[j] = active[i]->barriers[j];
			for (int j = 0; j < active[i]->platforms.size(); j++)
				P.platforms[j] = active[i]->platforms[j];
			for (int j = 0; j < active[i]->enemies.size(); j++)
				P.enemies[j] = active[i]->enemies[j];
		}
	}

	Sensor::Sensor() :Module(100, 1, true, 1, 5) {
		stype = 0;
		mtype = 2;
	}

	Sensor::Sensor(int t, int r, int les, int lec, bool p, int n, int j) : Module(les, lec, p, n, r) {
		i = j;
		stype = t;
		mtype = 2;
	}

	void Sensor::Get_info(Space &S, Platform& P){
		for (int i = 0; i < 2 * R; i++) {
			for (int j = 0; j < 2 * R; j++) {
				if(P.C.x - R + i >= 0 && P.C.y - R + j >= 0)
					if ((((P.C.x - R + i) - P.C.x) * ((P.C.x - R + i) - P.C.x) + ((P.C.y - R + j) - P.C.y) * ((P.C.y - R + j) - P.C.y)) <= (R + Sq) * (R + Sq)) {
						if (S.field[P.C.x - R + i][P.C.y - R + j]->get_type() == 1) {
							P.barriers[P.barriers.size()] = &S.field[P.C.x - R + i][P.C.y - R + j]->get_Cordinate();
							//P.n_barriers++;
						}
						if (S.field[P.C.x - R + i][P.C.y - R + j]->get_type() == 2) {
							P.platforms[P.platforms.size()] = &S.field[P.C.x - R + i][P.C.y - R + j]->get_Cordinate();
							//P.n_platforms++;
						}
						if (S.field[P.C.x - R + i][P.C.y - R + j]->get_type() == 3) {
							P.enemies[P.enemies.size()] = &S.field[P.C.x - R + i][P.C.y - R + j]->get_Cordinate();
							//P.n_enemies++;
						}
					}
			}
		}
	}

	Weapon::Weapon() :Module(100, 1, true, 1, 5) {
		T = 1;
		mtype = 3;
	}

	Weapon::Weapon(int t, int les, int lec, bool p, int n, int r, int j) : Module(les, lec, p, n, r) {
		i = j;
		T = t;
		mtype = 3;
	}

	void Weapon::Kill(Cordinate c, Space &S) {
		if (S.field[c.x][c.y]->get_type() == 3) {
			Enemy* enemy;
			enemy = dynamic_cast<Enemy*>(S.field[c.x][c.y]);
			enemy->destruction();
		}
	}

}