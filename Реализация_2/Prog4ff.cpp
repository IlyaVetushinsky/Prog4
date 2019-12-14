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
	  const char* msgs_network[] = { "0. Quit or select other module", "1. Get Partners", "2. Ask Partners" , "3. Take info" };
	const int NMsgs_network = sizeof(msgs_network) / sizeof(msgs_network[0]);
    	const char* msgs_sensor[] = { "0. Quit or select other module", "1. Scan space" };
	const int NMsgs_sensor = sizeof(msgs_sensor) / sizeof(msgs_sensor[0]);
	   const char* msgs_weapon[] = { "0. Quit or select other module", "1. Kill", "2. To charge", "3. From charge"};
	const int NMsgs_weapon = sizeof(msgs_weapon) / sizeof(msgs_weapon[0]);

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
		std::cout << "Imput max count of session (for sensor and weapon put any number)" << std::endl;
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
	//void Space::reset_Size(Cordinate c) {
	//	if (field != nullptr) {
	//		Cell*** field2 = new Cell * *[c.x];
	//		for (int i = 0; i < c.x; i++) {
	//			field2[i] = new Cell * [c.y];
	//		}
	//		for (int i = 0; i < c.x; i++) {
	//			for (int j = 0; j < c.y; j++) {
	//				if (i < Size.x && j < Size.y) {
	//					if (field[i][j]->get_type() == 0) {
	//						field2[i][j] = new Cell;
	//						field2[i][j]->C = field[i][j]->C;
	//						field2[i][j]->type = field[i][j]->type;
	//					}
	//					if (field[i][j]->get_type() == 1) {
	//						field2[i][j] = new Barrier;
	//						field2[i][j]->C = field[i][j]->C;
	//						field2[i][j]->type = field[i][j]->type;
	//					}
	//					if (field[i][j]->get_type() == 2) {
	//						field2[i][j]->pltype = 1;
	//						strcpy(description, "Empty platform");
	//						p_level_energy_supply = 100;
	//						n_slots = 10;
	//						n_slots_taked = 0;
	//					}
	//					if (field[i][j]->get_type() == 3) {
	//						//динамик каст
	//						field2[i][j] = new Enemy;
	//						field2[i][j]->C = field[i][j]->C;
	//						field2[i][j]->type = field[i][j]->type;

	//					}
	//					field2[i][j] = field[i][j];
	//				}
	//				delete field[i][j];
	//			}
	//			delete field[i];
	//		}
	//		delete field;
	//		field = field2;
	//		Size = c;
	//	}
	//}

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
					return { 1 , i };
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
		if (n_slots_taked + n > n_slots) {
			std::cout << "All slots are busy /n";
			return 0;
		}
		if (mt == 1) {
			static Network* net;
			net = new Network(les, lec, p, n, nms, r, mods.size());
			mods.push_back(net);
			//*mods[mods.size()] = Network(les, lec, p, n, nms, r, mods.size());
		}
			//mods.push_back(&Network(les, lec, p, n, nms, r, mods.size()));
			//*mods[sizeof(mods) / sizeof(Module)] = Network();
		if (mt == 2) {
			static Sensor* sens;
			sens = new Sensor(mt, r, les, lec, p, n, mods.size());
			mods.push_back(sens);
		}
			//*mods[sizeof(mods) / sizeof(Module)] = Sensor();
		if (mt == 3) {
			static Weapon* weap;
			weap = new Weapon(mt, les, lec, p, n, r, mods.size());
			mods.push_back(weap);
		}
		n_slots_taked += n;
		return 1;
			//*mods[sizeof(mods) / sizeof(Module)] = Weapon();
	//	n_mods++;
	}

	int Platform::delete_module(int mt, int les, int lec, int n, int nms, int r) {
		std::vector<Module*>::iterator iter;
		iter = mods.begin();
		int i = get_module_is(mt, les, lec, n, nms, r).y;
		if (i != -1) {
			mods.erase(iter + i);
			n_slots_taked -= n;
		}
		else {
			std::cout << "There is no such module/n";
			return 0;
		}
		return 1;
	}
	
	int Platform::get_network_is() {
		for (int i = 0; i < mods.size(); i++) {
			if (mods[i]->get_mtype() == 1)
				return mods[i]->get_R();
		}
		return -1;
	}
	void Platform::put_objects_info() {
		std::cout << "Enemies: ";
		for (int i = 0; i < enemies.size(); i++) {
			std::cout << enemies[i].x << ", " << enemies[i].y << std::endl;
		}
		std::cout << std::endl;
		std::cout << "Platforms: ";
		for (int i = 0; i < platforms.size(); i++) {
			std::cout << platforms[i].x << ", " << platforms[i].y << std::endl;
		}
		std::cout << std::endl;
		std::cout << "Barriers: ";
		for (int i = 0; i < barriers.size(); i++) {
			std::cout << barriers[i].x << ", " << barriers[i].y << std::endl;
		}
		std::cout << std::endl;
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
			if (S.field[C.x + 1][C.y]->get_type() == 0) { /////////////////////достать из массива барьеров
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

	void Network::put_active_Partners() {
		std::cout << "Cordinates of active partners:" << std::endl;
		for (int i = 0; i < active.size(); i++) {
			std::cout << active[i]->C.x << ", " << active[i]->C.y << std::endl;
		}
	}

	void Network::put_all_Partners() {
		std::cout << "Cordinates of all partners:" << std::endl;
		for (int i = 0; i < all.size(); i++) {
			std::cout << all[i]->C.x << ", " << all[i]->C.y << std::endl;
		}
	}

	void Network::get_Partners(Space &S, Platform &P) {
		active.clear();
		Platform* pl = nullptr;
		Module* mod = nullptr;
		Network* net = nullptr;
		for (int i = 0; i < P.platforms.size(); i++) {
			pl = dynamic_cast<Platform*>(S.field[P.platforms[i].x][P.platforms[i].y]);
			for (int j = 0; j < pl->mods.size(); j++) {
				if (pl->mods[j]->get_mtype() == 1 && pl->mods[j]->get_R() >= R) {
					set_Connection(P.C, { P.platforms[i].x , P.platforms[i].y });
					all.push_back(pl);
					active.push_back(pl);
				}
			}
		}
		//for (int i = 0; i < 2 * R; i++) {
		//	for (int j = 0; j < 2 * R; j++) {
		//		if (P.C.x - R + i >= 0 && P.C.y - R + j >= 0 && P.C.x - R + i < S.get_Size().x && P.C.y - R + j < S.get_Size().y) {
		//			if ((((P.C.x - R + i) - P.C.x) * ((P.C.x - R + i) - P.C.x) + ((P.C.y - R + j) - P.C.y) * ((P.C.y - R + j) - P.C.y)) <= (R + Sq) * (R + Sq)) {
		//				if (S.field[P.C.x - R + i][P.C.y - R + j]->get_type() == 2) {
		//					Cell* cell = S.field[P.C.x - R + i][P.C.y - R + j];
		//					Static_Platform* platform;
		//					platform = dynamic_cast<Static_Platform*>(cell);
		//					if (platform->get_network_is() != -1) {
		//						if (platform->get_network_is() >= R) { //return R
		//							set_Connection(P.C, { P.C.x - R + i, P.C.y - R + j });
		//							all.push_back(platform);
		//							active.push_back(platform);
		//						}
		//					}
		//				}
		//			}
		//		}
		//	}
		//}
	}

	void Network::set_Connection(Cordinate c1, Cordinate c2) {
		std::cout << "[" << c1.x << " , " << c1.y << "] - [" << c2.x << " , " << c2.y << "] : " << "Connection sucsess!" << std::endl;
	}


	std::vector<Platform*> Network::give_Partners() {
		return active;
	}

	void Network::ask_Partners(Cordinate c, Space &S, Platform &P) {
		Static_Platform* platform = nullptr;
		Module* module = nullptr;
		Network* network_module = nullptr;
		if (S.field[c.x][c.y]->get_type() == 2) {
			Cell* cell = S.field[c.x][c.y];
			platform = dynamic_cast<Static_Platform*>(cell);
			for (int j = 0; j < platform->mods.size(); j++) {
				if (platform->mods[j]->get_mtype() == 1 && platform->mods[j]->get_R() >= R) {
					network_module = dynamic_cast<Network*>(platform->mods[j]);
					for (int q = 0; q < network_module->give_Partners().size(); q++) {
						set_Connection(P.C, { P.platforms[q].x , P.platforms[q].y });
						if (network_module->give_Partners()[q]->get_Cordinate != P.get_Cordinate()) {
							all.push_back(network_module->give_Partners()[q]);
							active.push_back(network_module->give_Partners()[q]);
						}
					}
				}
			}
		}
	}

	void Network::take_info(Platform &P) {
		for (int i = 0; i < active.size(); i++) {
			for (int j = 0; j < active[i]->barriers.size(); j++)
				P.barriers.push_back(active[i]->barriers[j]);
			for (int j = 0; j < active[i]->platforms.size(); j++)
				P.platforms.push_back(active[i]->platforms[j]);
			for (int j = 0; j < active[i]->enemies.size(); j++)
				P.enemies.push_back(active[i]->enemies[j]);
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

	void Sensor::Get_info(Space& S, Platform& P) {
		P.barriers.clear();
		P.enemies.clear();
		P.platforms.clear();
		for (int i = 0; i < 2 * R; i++) {
			for (int j = 0; j < 2 * R; j++) {
				if(P.C.x - R + i >= 0 && P.C.y - R + j >= 0 && P.C.x - R + i < S.get_Size().x && P.C.y - R + j < S.get_Size().y)
					if (((((P.C.x - R + i) - P.C.x) * ((P.C.x - R + i) - P.C.x) + ((P.C.y - R + j) - P.C.y) * ((P.C.y - R + j) - P.C.y)) <= (R + Sq) * (R + Sq)) && (P.C.x - R + i != P.C.x || P.C.y - R + j != P.C.y) ) {
						if (S.field[P.C.x - R + i][P.C.y - R + j]->get_type() == 1) {
							P.barriers.push_back(S.field[P.C.x - R + i][P.C.y - R + j]->get_Cordinate());
						}
						if (S.field[P.C.x - R + i][P.C.y - R + j]->get_type() == 2) {
							P.platforms.push_back(S.field[P.C.x - R + i][P.C.y - R + j]->get_Cordinate());
						}
						if (S.field[P.C.x - R + i][P.C.y - R + j]->get_type() == 3) {
							P.enemies.push_back(S.field[P.C.x - R + i][P.C.y - R + j]->get_Cordinate());
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

	void Weapon::Kill(Platform& p, Space &S) {
		Cordinate c;
		if (!power) {
			std::cout << "Weapon off" << std::endl;
			return;
		}
		for (int i = 0; i < p.enemies.size(); i++) {
			c = p.enemies[i];
			if (((p.get_Cordinate().x - c.x) * (p.get_Cordinate().x - c.x) + (p.get_Cordinate().y - c.y) * (p.get_Cordinate().y - c.y)) <= (R + Sq) * (R + Sq)) {
				if (S.field[c.x][c.y]->get_type() == 3) {
					Enemy* enemy;
					enemy = dynamic_cast<Enemy*>(S.field[c.x][c.y]);
					enemy->destruction();
					p.enemies.pop_back();
					break;
				}
			}
		}
		std::cout << "No enemies within range" << std::endl;
	}

}