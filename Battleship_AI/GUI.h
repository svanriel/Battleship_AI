#pragma once

#include <iostream>
#include "Player.h"
#include "RealPlayer.h"
#include "AI.h" //this includes everything
#include "AI_Easy.cpp"

//arrays of guesses (note: grid_p1 are guesses by player one on player 2's setup)
int* grid_p1[10][10];
int* grid_p2[10][10];
//binary arrays of setups ('truth', where the ships are)
int* setup_p1[10][10];
int* setup_p2[10][10];

Player* player1;
Player* player2;

bool flag_turn; //turn of which player
bool flag_AI = true; //we are using an AI (instead of human opponent)

namespace Battleship_AI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;
	

	/// <summary>
	/// Summary for GUI
	/// </summary>
	public ref class GUI : public System::Windows::Forms::Form
	{
	public:
		GUI(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~GUI()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TabControl^  tabControl1;
	protected:
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::TabPage^  tabPage2;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::ComboBox^  comboBox2;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  gameInfo;

	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  label13;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->gameInfo = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->tabPage2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Location = System::Drawing::Point(12, 12);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(592, 469);
			this->tabControl1->TabIndex = 0;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->label8);
			this->tabPage1->Controls->Add(this->label6);
			this->tabPage1->Controls->Add(this->label5);
			this->tabPage1->Controls->Add(this->label4);
			this->tabPage1->Controls->Add(this->label3);
			this->tabPage1->Controls->Add(this->pictureBox1);
			this->tabPage1->Location = System::Drawing::Point(4, 25);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(584, 440);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Player 1";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(43, 420);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(304, 17);
			this->label8->TabIndex = 5;
			this->label8->Text = L"Guesses for Player 1: white is miss, red is a hit!";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(25, 400);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(15, 17);
			this->label6->TabIndex = 4;
			this->label6->Text = L"J";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(420, 19);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(24, 17);
			this->label5->TabIndex = 3;
			this->label5->Text = L"10";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(23, 42);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(17, 17);
			this->label4->TabIndex = 2;
			this->label4->Text = L"A";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(53, 19);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(16, 17);
			this->label3->TabIndex = 1;
			this->label3->Text = L"1";
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(46, 42);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(398, 375);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->label11);
			this->tabPage2->Controls->Add(this->label12);
			this->tabPage2->Controls->Add(this->label7);
			this->tabPage2->Controls->Add(this->label10);
			this->tabPage2->Controls->Add(this->label9);
			this->tabPage2->Controls->Add(this->pictureBox2);
			this->tabPage2->Location = System::Drawing::Point(4, 25);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(584, 440);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Player 2 (AI)";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(21, 387);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(15, 17);
			this->label11->TabIndex = 7;
			this->label11->Text = L"J";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(19, 41);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(17, 17);
			this->label12->TabIndex = 6;
			this->label12->Text = L"A";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(428, 14);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(24, 17);
			this->label7->TabIndex = 5;
			this->label7->Text = L"10";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(55, 14);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(16, 17);
			this->label10->TabIndex = 4;
			this->label10->Text = L"1";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(49, 418);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(131, 17);
			this->label9->TabIndex = 1;
			this->label9->Text = L"Player 2\'s guesses.";
			// 
			// pictureBox2
			// 
			this->pictureBox2->Location = System::Drawing::Point(43, 41);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(409, 374);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox2->TabIndex = 0;
			this->pictureBox2->TabStop = false;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(613, 159);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(118, 39);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Guess";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &GUI::button1_Click);
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(10) {
				L"1", L"2", L"3", L"4", L"5", L"6", L"7", L"8",
					L"9", L"10"
			});
			this->comboBox1->Location = System::Drawing::Point(610, 61);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(121, 24);
			this->comboBox1->TabIndex = 2;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(610, 38);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(97, 17);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Guess X (hor)";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(610, 88);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(96, 17);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Guess Y (ver)";
			// 
			// comboBox2
			// 
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Items->AddRange(gcnew cli::array< System::Object^  >(10) {
				L"A (1)", L"B (2)", L"C (3)", L"D (4)", L"E (5)",
					L"F (6)", L"G (7)", L"H (8)", L"I (9)", L"J (10)"
			});
			this->comboBox2->Location = System::Drawing::Point(610, 111);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(121, 24);
			this->comboBox2->TabIndex = 4;
			// 
			// gameInfo
			// 
			this->gameInfo->AutoSize = true;
			this->gameInfo->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->gameInfo->Location = System::Drawing::Point(6, 23);
			this->gameInfo->Name = L"gameInfo";
			this->gameInfo->Size = System::Drawing::Size(344, 32);
			this->gameInfo->TabIndex = 5;
			this->gameInfo->Text = L"Welcome to BattleShip AI!";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->gameInfo);
			this->groupBox1->Location = System::Drawing::Point(16, 483);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(690, 62);
			this->groupBox1->TabIndex = 6;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Game Info";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(606, 201);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(141, 17);
			this->label13->TabIndex = 7;
			this->label13->Text = L"* Use for AI move too";
			// 
			// GUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(743, 547);
			this->Controls->Add(this->label13);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->comboBox2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->tabControl1);
			this->Name = L"GUI";
			this->Text = L"GUI";
			this->Load += gcnew System::EventHandler(this, &GUI::GUI_Load);
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->tabPage2->ResumeLayout(false);
			this->tabPage2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
	//Put everything you want to do at startup here
	private: System::Void GUI_Load(System::Object^  sender, System::EventArgs^  e) {

		//set up the AI
		player1 = new RealPlayer();
		player2 = new AI();

		//setup board
		//initBoardSetup(setup_p1, true, true);
		//initBoardSetup(setup_p2, false, true);

		player1->createSetup();
		player2->createSetup();
		
		for (int y = 0; y < 10; y++) {
			for (int x = 0; x < 10; x++) {
				cout << player1->getSetup()[x][y] << " ";
			}
			cout << endl;
		}
		cout << endl;
		for (int y = 0; y < 10; y++) {
			for (int x = 0; x < 10; x++) {
				cout << player2->getSetup()[x][y] << " ";
			}
			cout << endl;
		}

		//player 1's turn
		flag_turn = false;

		updateScreen(player1->getGrid(), player2->getGrid());
		//updateScreen(player1->getSetup(), player2->getSetup()); //debug

	}

	//method describing a turn in which the playerAttacking tries to hit a ship of the playerAttacked
	private: void turn(Player *playerAttacking, Player *playerAttacked){
		int input[] = { comboBox1->SelectedIndex, comboBox2->SelectedIndex };
		int *moveArray = playerAttacking->move(input);
		int shootVal = playerAttacked->trialShotAt(moveArray);
		cout << "Shot " << moveArray[0] << ", " << moveArray[1] << " result: " << shootVal << endl;
		playerAttacking->afterShot(moveArray, shootVal);
	}
	
	//pbb not necessary anymore
	private: void initBoardSetup(int setup_p[10][10], bool isPlayer, bool defaultSettings) {
		setup_p[10][10];
		if (defaultSettings){
			//create a default setup
			setup_p[2][3] = 1;
			setup_p[3][3] = 1;
			setup_p[4][3] = 1;
			setup_p[0][0] = 1;
		}
		else if (isPlayer) {
			//player setup: player feedback
			//temporarily use default setup
			setup_p[2][3] = 1;
			setup_p[3][3] = 1;
			setup_p[4][3] = 1;
			setup_p[0][0] = 1;
		}
		else{
			//AI setup: use AI setup function
			//temporarily use default setup
			setup_p[2][3] = 1;
			setup_p[3][3] = 1;
			setup_p[4][3] = 1;
			setup_p[0][0] = 1;
		}
	}

	//This now works, don't look at it unless you need to (bleeeeeh UI graphics that aren't really made for this)
	private: void updateScreen(int (&grid_p1)[10][10], int (&grid_p2)[10][10]) {
		Bitmap^ bitmap1 = gcnew Bitmap(300, 300);
		Bitmap^ bitmap2 = gcnew Bitmap(300, 300);
		for (int i = 0; i < 299; i++) {
			for (int j = 0; j < 299; j++) {
				switch (grid_p1[i / 30][j / 30]) {
				case 2:
					bitmap1->SetPixel(i, j, System::Drawing::Color::Red);
					break;
				case 1:
					bitmap1->SetPixel(i, j, System::Drawing::Color::White);
					break;
				default:
					bitmap1->SetPixel(i, j, System::Drawing::Color::Blue);
					break;
				}
				switch (grid_p2[i / 30][j / 30]) {
				case 2:
					bitmap2->SetPixel(i, j, System::Drawing::Color::Red);
					break;
				case 1:
					bitmap2->SetPixel(i, j, System::Drawing::Color::White);
					break;
				default:
					bitmap2->SetPixel(i, j, System::Drawing::Color::Blue);
					break;
				}
				//borders and squares
				if (i % 30 == 0 || j % 30 == 0) {
					bitmap1->SetPixel(i, j, System::Drawing::Color::Black);
					bitmap2->SetPixel(i, j, System::Drawing::Color::Black);
				}
			}
			//cout << endl;
		}
		pictureBox1->Image = bitmap1;
		pictureBox2->Image = bitmap2;
	}

	//Click the guess-button
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		
		//valid move?
		if (comboBox1->SelectedIndex != -1 && comboBox2->SelectedIndex != -1) 
		{
			//player 1
			if (!flag_turn)
			{				
				turn(player1, player2);

				updateScreen(player1->getGrid(),player2->getGrid());
				//updateScreen(player1->getSetup(), player2->getSetup()); //debug mode
				gameInfo->Text = "Player 2's move.";		
			}
		//player 2
			else
			{
				turn(player2, player1);
				/*{
					//check if guess correct (if there is a boat at [selected,selected])
					if (setup_p1[comboBox1->SelectedIndex][comboBox2->SelectedIndex] == 1)
						grid_p2[comboBox1->SelectedIndex][comboBox2->SelectedIndex] = 2;
					else
						grid_p2[comboBox1->SelectedIndex][comboBox2->SelectedIndex] = 1;
				}*/
				updateScreen(player1->getGrid(), player2->getGrid());
				//updateScreen(player1->getSetup(), player2->getSetup()); //debug mode
				gameInfo->Text = "Player 1's move.";
			}

		//change turn
		flag_turn = !flag_turn;
		}
		else
			cout << "Please enter a valid field." << endl;

	}
};
}
