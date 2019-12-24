#include <iostream>
#include "Header.h"
#include "MyVec.h"
using namespace Prog4_app;
using namespace Prog4;
int main(){
	std::cout << "Create your Space!" << std::endl;
	Cordinate c = input_c();
	Space S1(c);
	std::cout << S1.get_Size().x << std::endl << S1.get_Size().y << std::endl << std::endl;
	S1.print(std::cout);
	Cell* cell = nullptr;
	Platform* platform = nullptr;
	Static_Platform* static_platform = nullptr;
	Mobile_Platform* mobile_platform = nullptr;
	Module* module = nullptr;
	int rc;
	Cordinate eis = {-1,-1};
	std::cout << "Now add objects to your field" << std::endl;
	while (rc = dialog(msgs1, NMsgs1)) {
		if (rc == 0) {
			if (eis.x == -1 && eis.y == -1) {
				std::cout << "Add enemy to your field !" << std::endl;
				rc = 1;
			}
		}
		if (rc == 1) {
			std::cout << "Input cordinate of new object" << std::endl;
			Cordinate c = input_c();
			int t;
			std::cout << "Input type of object : 0-empty cell, 1-barrier, 2- static platform, 3-mobile platform, 4-enemy" << std::endl;
			while (getNum(t) < 0 || t < 0 || t > 4)
			{
				std::cout << "You're wrong. Repeat please" << std::endl;
			}
			int les = 0;
			int ns = 0;
			int v = 1;
			if (t == 2 || t == 3) {
				std::cout << "Input level energy supply" << std::endl;
				while (getNum(les) < 0)
				{
					std::cout << "You're wrong. Repeat please" << std::endl;
				}
				std::cout << "Input count of slots" << std::endl;
				while (getNum(ns) < 0)
				{
					std::cout << "You're wrong. Repeat please" << std::endl;
				}
			}
			if (t == 3 || t == 4) {
				std::cout << "Input speed" << std::endl;
				while (getNum(v) < 0)
				{
					std::cout << "You're wrong. Repeat please" << std::endl;
				}
			}
			if (t == 4 && eis.x == -1) {
				eis = c;
			}
			else
				if (t == 4 && eis.x != -1) {
					std::cout << "There is enemy already" << std::endl;
					continue;
				}
			if (S1.add_object(t, c, 0, v, les, ns)) {
				std::cout << "This cell is busy. If you want to add anyway put 1" << std::endl;
				int r;
				while (getNum(r) < 0)
				{
					std::cout << "You're wrong. Repeat please" << std::endl;
				}
				if (r == 1)
					S1.add_object(t, c, 1, les, ns, v);
			}
			S1.print(std::cout);
			continue;
		}
		if (rc == 2) {
			std::cout << "Input new size by X and Y" << std::endl;
			Cordinate c = input_c();
			S1.reset_Size(c);
			S1.print(std::cout);
			continue;
		}
		if (rc == 3) {
			std::cout << "Input cordinates of object" << std::endl;
			Cordinate c = input_c();
			cell = S1.return_object(c);
			std::cout << "Type: " << cell->get_type() << std::endl;
		}
		if (rc == 4) {
			S1.print(std::cout);
			continue;
		}
		if (cell->get_type() == 0 || cell->get_type() == 1) {
			while (rc = dialog(msgs_cell, NMsgs_cell)) {
				if (rc == 1) {
					std::cout << "Type: " << cell->get_type() << std::endl;
				}
				if (rc == 2) {
					std::cout << "Cordinate: " << cell->get_Cordinate().x << " ," << cell->get_Cordinate().y << std::endl;
				}
			}
		}
		if (cell->get_type() == 2) {
			platform = dynamic_cast<Platform*>(cell);
			while (rc = dialog(msgs_platform, NMsgs_platform)) {
				if (rc == 1) {
					std::cout << "Type: " << cell->get_type() << std::endl;
					continue;
				}
				if (rc == 2) {
					std::cout << "Cordinate: " << cell->get_Cordinate().x << " ," << cell->get_Cordinate().y << std::endl;
					continue;
				}
				if (rc == 3) {
					std::cout << "Type: " << platform->get_pltype() << std::endl;
					continue;
				}
				if (rc == 4) {
					int mt, les, lec, n, nms, r;
					input_module_properties(mt, les, lec, n, nms, r);
					bool p = true;
					platform->add_module(mt, les, lec, p, n, nms, r);
					continue;
				}
				if (rc == 5) {
					int mt, les, lec, n, nms, r;
					input_module_properties(mt, les, lec, n, nms, r);
					if (platform->get_module_is(mt, les, lec, n, nms, r).x == 1) {
						std::cout << "Found!" << std::endl;
					}
					else {
						std::cout << " Not found!" << std::endl;
					}
					continue;
				}
				if (rc == 6) {
					platform = dynamic_cast<Platform*>(cell);
					int mt, les, lec, n, nms, r;
					input_module_properties(mt, les, lec, n, nms, r);
					//platform->delete_module(mt, les, lec, n, nms, r);
					continue;
				}
				if (rc == 7) {
					platform = dynamic_cast<Platform*>(cell);
					if (platform->get_pltype() == 2) {
						Mobile_Platform* mob_pl = dynamic_cast<Mobile_Platform*>(platform);
						std::cout << "Input where enemy should move : 4862" << std::endl;
						int r;
						while (getNum(r) < 0 && r != 4 && r != 6 && r != 2 && r != 8)
						{
							std::cout << "You're wrong. Repeat please" << std::endl;
						}
						std::cout << std::endl;
						mob_pl->Move(r, S1);
						S1.print(std::cout);
					}
					else {
						std::cout << "Static platform can't moves" << std::endl;
					}
					continue;
				}
				if (rc == 8) {

				}
			}
		}
		if (cell->get_type() == 3) {
			while (rc = dialog(msgs_enemy, NMsgs_enemy)) {
				if (rc == 1) {
					std::cout << "Type: " << cell->get_type() << std::endl;
				}
				if (rc == 2) {
					std::cout << "Cordinate: " << cell->get_Cordinate().x << " ," << cell->get_Cordinate().y << std::endl;
				}
				if (rc == 3) {
					Enemy* enemy = dynamic_cast<Enemy*>(cell);
					std::cout << "Input where enemy should move : 4862" << std::endl;
					int r;
					while (getNum(r) < 0 && r != 4 && r != 6 && r != 2 && r != 8)
					{
						std::cout << "You're wrong. Repeat please" << std::endl;
					}
					std::cout << std::endl;
					if (!(enemy = enemy->move(r, S1)))
						std::cout << "This cell is busy" << std::endl << std::endl;
					else
						cell = enemy;
					S1.print(std::cout);
				}
			}
		}
	}
	std::cout << "Let's start!" << std::endl << std::endl;
	Cell* enemy = S1.return_object(eis);
	Prog4::vector < Platform* > S_platforms;
	for (int i = 0; i < S1.get_Size().x; i++) {
		for (int j = 0; j < S1.get_Size().y; j++) {
			Cell* obj = S1.return_object({ i,j });
			if (obj->get_type() == 2) {
				Platform* pl = dynamic_cast<Platform*>(obj);
				S_platforms.push_back(pl);
			}
		}
	}
	S1.print(std::cout);
	while (enemy->get_type() == 3) {
		/*
		-Нарушитель(если не убит):
		1)сделать ход
		-Платформы:
		1)Сканирование местности сенсором
		2)Поиск партнеров и создание соединений
		3)передача информации на платформу
		4)Выстрел(если враг обнаружен и в радиусе Weapon)
		-Платформы:
		1)Сделать ход
		*/


		Enemy* real_enemy = dynamic_cast<Enemy*>(enemy);
		for (int n = 0; n < real_enemy->return_V(); n++) {
			real_enemy->move_alg(S1);
		}


		S1.print(std::cout);


		for (int i = 0; i < S_platforms.size(); i++) {
			if (S_platforms[i]->return_module(2,0) != nullptr) {
				Module* mod = S_platforms[i]->return_module(2, 0);
				mod->get_energy(mod->get_level_energy_supply() + S_platforms[i]->get_les());
				if (mod && mod->get_level_energy() - mod->get_level_energy_cons() >= 0) {
					Sensor* sens = dynamic_cast<Sensor*>(mod);
					sens->Get_info(S1, *(S_platforms[i]));
					sens->spend_energy(sens->get_level_energy_cons());
				}
			}
		}


		for (int i = 0; i < S_platforms.size(); i++) {
			if (S_platforms[i]->return_module(1, 0) != nullptr) {
				Module* mod = S_platforms[i]->return_module(1, 0);
				mod->get_energy(mod->get_level_energy_supply() + S_platforms[i]->get_les());
				if (mod && mod->get_level_energy() - mod->get_level_energy_cons() >= 0) {
					Network* net = dynamic_cast<Network*>(mod);
					if (net->get_sessions() < net->get_n_max_session()) {
						net->add_session(1);
						net->get_Partners(S1, *(S_platforms[i]));
						net->spend_energy(net->get_level_energy_cons());
					}
				}
			}
		}


		for (int i = 0; i < S_platforms.size(); i++) {
			if (S_platforms[i]->return_module(1, 0) != nullptr) {
				Module* mod = S_platforms[i]->return_module(1, 0);
				if (mod && mod->get_level_energy() - mod->get_level_energy_cons() >= 0) {
					Network* net = dynamic_cast<Network*>(mod);
					Prog4::vector<Cordinate> active_Cords = net->get_active_cordinates();
					int q = 0;
					while (net->get_sessions() < net->get_n_max_session() && q < active_Cords.size() && net->get_level_energy() > 0) {
						net->add_session(1);
						net->ask_Partners(active_Cords[q], S1, *(S_platforms[i]));
						net->spend_energy(net->get_level_energy_cons());
						q++;
						active_Cords = net->get_active_cordinates();
					}
					net->take_info(*(S_platforms[i]));
					net->dic_session(1);
				}
			}
		}


		Platform* plat = nullptr;
		for (int i = 0; i < S_platforms.size(); i++) {
			if (S_platforms[i]->get_pltype() == 2) {
				plat = S_platforms[i];
				int s = plat->find_stp_in_active();
				if (s == 0) {
					S_platforms.erase(S_platforms.begin());// + i);
				}
			}	
		}
			

		int ind_k = 1;
		for (int i = 0; i < S_platforms.size(); i++) {
			if (S_platforms[i]->return_module(3, 0) != nullptr) {
				Module* mod = S_platforms[i]->return_module(3, 0);
				mod->get_energy(mod->get_level_energy_supply() + S_platforms[i]->get_les());
				if (mod && mod->get_level_energy() - mod->get_level_energy_cons() >= 0) {
					Weapon* weap = dynamic_cast<Weapon*>(mod);
					ind_k = weap->Kill(*(S_platforms[i]), S1);
					weap->spend_energy(weap->get_level_energy_cons());
				}
			}
		}


		int k = 0;
		for (int i = 0; i < S_platforms.size(); i++) {
			if (S_platforms[i]->get_enemy_is().x != -1 && S_platforms[i]->get_enemy_is().y != -1) {
				k++;
			}
		}


		if (k != 0) {// если нарушитель обнаружен
			for (int i = 0; i < S_platforms.size(); i++) {
				if (S_platforms[i]->get_pltype() == 2 && S_platforms[i]->get_network_is() != -1) {
					Mobile_Platform* mpl = dynamic_cast<Mobile_Platform*>(S_platforms[i]);
					if (mpl->get_enemy_is().x != -1 && mpl->get_enemy_is().y != -1) {
						for (int t = 0; t < mpl->get_V(); t++)
							mpl->go_to(mpl->get_enemy_is(), S1);
					}
				}
			}
		}
		else {// если нарушитель не обнаружен
			int a = rand();
			for (int i = 0; i < S_platforms.size(); i++) {
				if (S_platforms[i]->get_pltype() == 2) {
					Mobile_Platform* mpl = dynamic_cast<Mobile_Platform*>(S_platforms[i]);
					if (mpl->get_network_is() != -1) {
						Network* net = dynamic_cast<Network*>(mpl->return_module(1, 0));
						Cordinate cc;
						int t = net->return_max_able_stp(*mpl, cc);
						Platform* stpl = dynamic_cast<Platform*>(S1.return_object(cc));
						int r = mpl->return_module(1, 0)->get_R();
						if (r > stpl->return_module(1, 0)->get_R())
							r = stpl->return_module(1, 0)->get_R();
						int k = 0;
						for (int t = 0; t < mpl->get_V(); t++) {
							if (a % 4 == 0 && r - sqrt((mpl->get_Cordinate().x - cc.x) * (mpl->get_Cordinate().x - cc.x) + (mpl->get_Cordinate().y - cc.y + 1) * (mpl->get_Cordinate().y - cc.y + 1)) > Sq + 1) {
								if (mpl->Move(8, S1) == 1)
									k = 1;
								else
									a++;
							}
							if (a % 4 == 1 && r - sqrt((mpl->get_Cordinate().x - 1 - cc.x) * (mpl->get_Cordinate().x - 1 - cc.x) + (mpl->get_Cordinate().y - cc.y) * (mpl->get_Cordinate().y - cc.y)) > Sq + 1) {
								if (mpl->Move(4, S1) == 1)
									k = 1;
								else
									a++;
							}
							if (a % 4 == 2 && r - sqrt((mpl->get_Cordinate().x - cc.x) * (mpl->get_Cordinate().x - cc.x) + (mpl->get_Cordinate().y - cc.y - 1) * (mpl->get_Cordinate().y - cc.y - 1)) > Sq + 1) {
								if (mpl->Move(2, S1) == 1)
									k = 1;
								else
									a++;
							}
							if (a % 4 == 3 && r - sqrt((mpl->get_Cordinate().x + 1 - cc.x) * (mpl->get_Cordinate().x + 1 - cc.x) + (mpl->get_Cordinate().y - cc.y) * (mpl->get_Cordinate().y - cc.y)) > Sq + 1) {
								if (mpl->Move(6, S1) == 1)
									k = 1;
								else
									a++;
							}
						}
					}
				}
			}
		}
		S1.print(std::cout);
	}
	std::cout << "Enemy killed!" << std::endl << std::endl;
	return 1;
}