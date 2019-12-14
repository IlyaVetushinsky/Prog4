#ifndef _PROG4H_
#define _PROG4H_
#include <iostream>
#include <vector>
#pragma warning(disable : 4996)
namespace Prog4{
	const double Sq = 0.708;
	struct Cordinate {
		int x;
		int y;
	};
	class Cell;
	class Barrier;
	class Platform;
	class Module;
	class Enemy;
	class Static_Platform;
	class Mobile_Platform;
	class Network;
	class Sensor;
	class Weapon;
	class Space {
	private:
		Cordinate Size;
		Cell*** field;
	public:
		Space();
		Space(Cordinate c);
		Cell* return_object(Cordinate c) { return field[c.x][c.y]; }
		Cordinate get_Size() { return Size; }
		void set_Size(Cordinate c);
		void reset_Size(Cordinate c);
		int add_object(int type, Cordinate c, int ind, int v, int les, int ns);
		std::ostream& print(std::ostream&) const;
		~Space();
		friend Enemy;
		friend Mobile_Platform;
		friend Weapon;
		friend Sensor;
		friend Network;
	};
	class Cell { // type == 0
	protected:
		int type;
		Cordinate C;
	public:
		int get_type() { return type; }
		Cordinate get_Cordinate() { return C; }
		Cell();
		Cell(Cordinate c, int t);
		friend Space;
		virtual ~Cell() { ; }
	};
	class Barrier : public Cell{ // type == 1
	public:
		Barrier();
		Barrier(Cordinate c);
		friend Space;
	};
	class Platform : public Cell {  // type == 2
	protected:
		int pltype; 
		char description[1000];
		int p_level_energy_supply;
		int n_slots;
		int n_slots_taked;
		//int n_mods;
		//int n_enemies;
		//int n_barriers;
		//int n_platforms;
		std::vector<Module*> mods;
		//Module** mods;
		std::vector < Cordinate> enemies; //sensor
		std::vector < Cordinate> barriers; //sensor
		std::vector < Cordinate> platforms; //sensor
		friend Space;
		friend Network;
		friend Sensor;
		friend Weapon;
	public:
		virtual int get_pltype() { return pltype; }
		virtual Cordinate get_module_is(int mt, int les, int lec, int n, int nms, int r);
		virtual int get_network_is();
		virtual Module* return_module(int i) { return mods[i]; }
		//void change_discription(char*);
		virtual void put_objects_info();
		Platform();
		Platform(Cordinate, int les, int ns);
		virtual int add_module(int mt, int les, int lec, bool p, int n, int nms, int r);
		virtual int delete_module(int t, int les, int lec, int n, int nms, int r);
		virtual ~Platform() { ; }
	};
	class Enemy : public Cell {  // type == 3
	public:
		Enemy();
		Enemy(Cordinate c);
		Enemy* move(int k, Space& S);
		void destruction();
		friend Space;
	};
	class Static_Platform : public Platform { // pltype == 1
	public:
		Static_Platform();
		Static_Platform(Cordinate, int les, int ns);
		~Static_Platform();
		friend Space;
	};
	class Mobile_Platform : public Platform {  // pltype == 2
	private:
		int V;
	public:
		Mobile_Platform();
		Mobile_Platform(Cordinate c, int les, int ns, int v);
		Mobile_Platform* Move(int k, Space&);
		~Mobile_Platform();
		friend Space;
	};
	class Module {
	protected:
		int i;
		int R;
		int mtype; 
		int level_energy_supply;
		int level_energy_cons;
		bool power;
		int n_slots_take;
		void Power_on() { power = true; }
		void Power_off() { power = false; }
	public:
		Module();
		virtual int get_mtype() { return mtype; }
		virtual int get_n_slots_take() {return n_slots_take; }
		virtual int get_level_energy_supply() { return level_energy_supply; }
		virtual int get_level_energy_cons() { return level_energy_cons; }
		virtual int get_R() { return R; }
		Module(int les, int lec, bool p, int nm, int r);
		friend Space;
		virtual ~Module() { ; }
	};
	class Network : public Module { //mtype == 1
	protected:
		int n_max_session;
		int session;
		//int n_active;
		//int n_all;
		std::vector<Platform*> active;
		std::vector<Platform*> all;
	public:
		Network();
		Network(int les, int lec, bool p, int n, int nms, int r, int i);
		int get_n_max_session() { return n_max_session; }
		void get_Partners(Space&, Platform&);
		void put_all_Partners();
		void put_active_Partners();
		std::vector<Platform*> give_Partners();
		void set_Partners(std::vector<Platform*> a) { active = a; }
		void set_Connection(Cordinate, Cordinate);
		void ask_Partners(Cordinate, Space&, Platform&);
		void take_info(Platform&);
		~Network() { ; }
		friend Space;
	};
	class Sensor : public Module {  //mtype == 2
	protected:
		int stype;
	public:
		Sensor();
		Sensor(int, int, int les, int lec, bool p, int n, int i);
		void Get_info(Space&, Platform&);
		friend Space;
	};
	class Weapon : public Module {  //mtype == 3
	protected:
		int T;
	public:
		Weapon();
		Weapon(int, int les, int lec, bool p, int n, int r, int i);
		void Kill(Platform&, Space&);
		void inCharge() { Power_off(); }
		void outCharge() { Power_on(); }
		friend Space;
	};
	extern const char* msgs1[];
	extern const char* msgs_cell[];
	extern const char* msgs_platform[];
	extern const char* msgs_enemy[];
	extern const char* msgs_network[];
	extern const char* msgs_sensor[];
	extern const char* msgs_weapon[];
	extern const int NMsgs1, NMsgs_cell, NMsgs_barrier, NMsgs_platform, NMsgs_enemy, NMsgs_network, NMsgs_sensor, NMsgs_weapon;
	int dialog(const char* msgs[], int);
	int getNum(int& a);
	Cordinate input_c();
	void input_module_properties(int&, int&, int&, int&, int&, int&);
}
#endif
#pragma once