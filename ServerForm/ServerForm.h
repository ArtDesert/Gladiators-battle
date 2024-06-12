#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <winsock2.h>
#include <vector>
#include <string>
#include "Gladiator.h"
#include "ResultsTable.h"
#include "QueueTable.h"
#include <process.h>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)
#pragma once

namespace oslab6 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	std::vector<Gladiator*> allGlads; //Набор всех соединений, находящихся в очереди
	std::vector<Gladiator*> glads; //Набор соединений, работающих на сервере в данный момент
	WSAData wsaData;
	WORD Dllversion = MAKEWORD(2, 1);
	SOCKET sListen;
	int i = 0;
	SOCKADDR_IN addr;
	int sizeofAddr = sizeof(addr);

	/// <summary>
	/// Сводка для ServerForm
	/// </summary>
	public ref class ServerForm : public System::Windows::Forms::Form
	{
	public:
		ServerForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~ServerForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::ComponentModel::BackgroundWorker^ backgroundWorker1;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::Button^ button5;
	private: System::Windows::Forms::Button^ button6;
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ таблицаToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ таблицаРезультатовToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ таблицаЖдущихToolStripMenuItem;
	public: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::RichTextBox^ richTextBox1;
	private: System::Windows::Forms::Button^ button7;

	public: DataTable^ rTable, ^ qTable;
		  ResultsTable^ r;
		  QueueTable^ q;
		  bool CanStartTheBattle = false;
		  Gladiator* first = NULL, * second = NULL;
	private: System::Windows::Forms::Button^ button8;

	//private: System::Windows::Forms::SaveFileDialog^ saveFileDialog1;
	//private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;


	private: System::Windows::Forms::ColorDialog^ colorDialog1;

	public:

	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->таблицаToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->таблицаРезультатовToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->таблицаЖдущихToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->colorDialog1 = (gcnew System::Windows::Forms::ColorDialog());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::SystemColors::Control;
			this->label1->Cursor = System::Windows::Forms::Cursors::Default;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 26.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->ForeColor = System::Drawing::Color::Teal;
			this->label1->Location = System::Drawing::Point(62, 24);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(715, 39);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Добро пожаловать на гладиаторские игры!";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label1->Click += gcnew System::EventHandler(this, &ServerForm::label1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->ForeColor = System::Drawing::Color::Teal;
			this->label2->Location = System::Drawing::Point(269, 167);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(136, 24);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Текущая пара:";
			this->label2->Click += gcnew System::EventHandler(this, &ServerForm::label2_Click);
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::RoyalBlue;
			this->button1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->button1->Location = System::Drawing::Point(175, 77);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(230, 60);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Добавить фракийца";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &ServerForm::button1_Click);
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(170)),
				static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->button2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button2->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->button2->Location = System::Drawing::Point(411, 77);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(230, 60);
			this->button2->TabIndex = 3;
			this->button2->Text = L"Добавить самнита";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &ServerForm::button2_Click);
			// 
			// backgroundWorker1
			// 
			this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &ServerForm::backgroundWorker1_DoWork);
			// 
			// button3
			// 
			this->button3->BackColor = System::Drawing::Color::IndianRed;
			this->button3->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button3->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->button3->Location = System::Drawing::Point(98, 221);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(200, 40);
			this->button3->TabIndex = 6;
			this->button3->Text = L"Отключить первого ";
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Click += gcnew System::EventHandler(this, &ServerForm::button3_Click);
			// 
			// button4
			// 
			this->button4->BackColor = System::Drawing::Color::IndianRed;
			this->button4->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button4->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->button4->Location = System::Drawing::Point(304, 221);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(200, 40);
			this->button4->TabIndex = 7;
			this->button4->Text = L"Отключить второго";
			this->button4->UseVisualStyleBackColor = false;
			this->button4->Click += gcnew System::EventHandler(this, &ServerForm::button4_Click);
			// 
			// button5
			// 
			this->button5->BackColor = System::Drawing::Color::IndianRed;
			this->button5->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button5->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button5->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->button5->Location = System::Drawing::Point(510, 221);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(200, 40);
			this->button5->TabIndex = 8;
			this->button5->Text = L"Отключить обоих";
			this->button5->UseVisualStyleBackColor = false;
			this->button5->Click += gcnew System::EventHandler(this, &ServerForm::button5_Click);
			// 
			// button6
			// 
			this->button6->BackColor = System::Drawing::Color::MediumSeaGreen;
			this->button6->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button6->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button6->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->button6->Location = System::Drawing::Point(411, 524);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(230, 60);
			this->button6->TabIndex = 9;
			this->button6->Text = L"Начать битву";
			this->button6->UseVisualStyleBackColor = false;
			this->button6->Click += gcnew System::EventHandler(this, &ServerForm::button6_Click);
			// 
			// menuStrip1
			// 
			this->menuStrip1->BackColor = System::Drawing::SystemColors::Control;
			this->menuStrip1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->menuStrip1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->menuStrip1->GripStyle = System::Windows::Forms::ToolStripGripStyle::Visible;
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->таблицаToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->RenderMode = System::Windows::Forms::ToolStripRenderMode::Professional;
			this->menuStrip1->Size = System::Drawing::Size(834, 25);
			this->menuStrip1->TabIndex = 10;
			this->menuStrip1->Text = L"menuStrip1";
			this->menuStrip1->ItemClicked += gcnew System::Windows::Forms::ToolStripItemClickedEventHandler(this, &ServerForm::menuStrip1_ItemClicked_1);
			// 
			// таблицаToolStripMenuItem
			// 
			this->таблицаToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->таблицаРезультатовToolStripMenuItem,
					this->таблицаЖдущихToolStripMenuItem
			});
			this->таблицаToolStripMenuItem->Name = L"таблицаToolStripMenuItem";
			this->таблицаToolStripMenuItem->Size = System::Drawing::Size(72, 21);
			this->таблицаToolStripMenuItem->Text = L"Таблицы";
			// 
			// таблицаРезультатовToolStripMenuItem
			// 
			this->таблицаРезультатовToolStripMenuItem->Name = L"таблицаРезультатовToolStripMenuItem";
			this->таблицаРезультатовToolStripMenuItem->Size = System::Drawing::Size(203, 22);
			this->таблицаРезультатовToolStripMenuItem->Text = L"Таблица результатов";
			this->таблицаРезультатовToolStripMenuItem->Click += gcnew System::EventHandler(this, &ServerForm::таблицаРезультатовToolStripMenuItem_Click);
			// 
			// таблицаЖдущихToolStripMenuItem
			// 
			this->таблицаЖдущихToolStripMenuItem->Name = L"таблицаЖдущихToolStripMenuItem";
			this->таблицаЖдущихToolStripMenuItem->Size = System::Drawing::Size(203, 22);
			this->таблицаЖдущихToolStripMenuItem->Text = L"Таблица ждущих";
			this->таблицаЖдущихToolStripMenuItem->Click += gcnew System::EventHandler(this, &ServerForm::таблицаЖдущихToolStripMenuItem_Click);
			// 
			// textBox1
			// 
			this->textBox1->BackColor = System::Drawing::SystemColors::Info;
			this->textBox1->Cursor = System::Windows::Forms::Cursors::Arrow;
			this->textBox1->Enabled = false;
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Franklin Gothic Medium", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox1->Location = System::Drawing::Point(430, 162);
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->Size = System::Drawing::Size(136, 29);
			this->textBox1->TabIndex = 11;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &ServerForm::textBox1_TextChanged);
			// 
			// textBox2
			// 
			this->textBox2->BackColor = System::Drawing::SystemColors::Info;
			this->textBox2->Cursor = System::Windows::Forms::Cursors::No;
			this->textBox2->Enabled = false;
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Franklin Gothic Medium", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox2->Location = System::Drawing::Point(609, 162);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(136, 29);
			this->textBox2->TabIndex = 12;
			this->textBox2->TextChanged += gcnew System::EventHandler(this, &ServerForm::textBox2_TextChanged);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(572, 166);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(31, 20);
			this->label3->TabIndex = 13;
			this->label3->Text = L"VS";
			this->label3->Click += gcnew System::EventHandler(this, &ServerForm::label3_Click_1);
			// 
			// richTextBox1
			// 
			this->richTextBox1->BackColor = System::Drawing::SystemColors::Info;
			this->richTextBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->richTextBox1->Cursor = System::Windows::Forms::Cursors::IBeam;
			this->richTextBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->richTextBox1->Location = System::Drawing::Point(81, 267);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->ReadOnly = true;
			this->richTextBox1->Size = System::Drawing::Size(654, 251);
			this->richTextBox1->TabIndex = 14;
			this->richTextBox1->Text = L"";
			this->richTextBox1->TextChanged += gcnew System::EventHandler(this, &ServerForm::richTextBox1_TextChanged);
			// 
			// button7
			// 
			this->button7->BackColor = System::Drawing::Color::MediumSeaGreen;
			this->button7->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button7->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button7->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->button7->Location = System::Drawing::Point(175, 524);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(230, 60);
			this->button7->TabIndex = 15;
			this->button7->Text = L"Покинуть игры";
			this->button7->UseVisualStyleBackColor = false;
			this->button7->Click += gcnew System::EventHandler(this, &ServerForm::button7_Click);
			// 
			// button8
			// 
			this->button8->BackColor = System::Drawing::Color::IndianRed;
			this->button8->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button8->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button8->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->button8->Location = System::Drawing::Point(43, 160);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(200, 40);
			this->button8->TabIndex = 16;
			this->button8->Text = L"Определить пару";
			this->button8->UseVisualStyleBackColor = false;
			this->button8->Click += gcnew System::EventHandler(this, &ServerForm::button8_Click);
			// 
			// ServerForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->ClientSize = System::Drawing::Size(834, 602);
			this->Controls->Add(this->button8);
			this->Controls->Add(this->button7);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->menuStrip1);
			this->Cursor = System::Windows::Forms::Cursors::Arrow;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->HelpButton = true;
			this->MaximizeBox = false;
			this->Name = L"ServerForm";
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Show;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Гладиаторские игры";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &ServerForm::ServerForm_FormClosing);
			this->Load += gcnew System::EventHandler(this, &ServerForm::ServerForm_Load);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
		void Log(String^ info)
		{
			StreamWriter^ sw = gcnew StreamWriter("applog.txt", true);
			sw->WriteLine(info);
			sw->Close();
		}

#pragma endregion
		void KillProcess(int PID)
		{
			std::string killCommand("Taskkill /f /pid ");
			killCommand.append(std::to_string(PID)).append(" /t");
			system(killCommand.data());
		}
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		//WinExec("Thracian.exe", SW_SHOW);
		PROCESS_INFORMATION pi = { 0 };
		STARTUPINFO sti = { 0 };
		wstring CommandLine(L"Thracian.exe");
		LPWSTR lpwCmdLine = &CommandLine[0];
		CreateProcess(NULL, lpwCmdLine, NULL, NULL, TRUE, NULL, NULL, NULL, &sti, &pi);
		int curPID = pi.dwProcessId;
		char c = '0' + i;
		SOCKET newSocket = accept(sListen, (SOCKADDR*)&addr, &sizeofAddr);
		send(newSocket, &c, sizeof(c), NULL);
		Gladiator* newGladiator = new Gladiator(newSocket, "Фракиец", i, curPID);
		allGlads.push_back(newGladiator);
		qTable->Rows->Add(i, "Фракиец", curPID);
		Log("Клиент " + i + " (Фракиец) подключился");
		++i;
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {

		//WinExec("Samnite.exe", SW_SHOW);
		PROCESS_INFORMATION pi = { 0 };
		STARTUPINFO sti = { 0 };
		wstring CommandLine(L"Samnite.exe");
		LPWSTR lpwCmdLine = &CommandLine[0];
		CreateProcess(NULL, lpwCmdLine, NULL, NULL, TRUE, NULL, NULL, NULL, &sti, &pi);
		int curPID = pi.dwProcessId;
		char c = '0' + i;
		SOCKET newSocket = accept(sListen, (SOCKADDR*)&addr, &sizeofAddr);
		send(newSocket, &c, sizeof(c), NULL);
		Gladiator* newGladiator = new Gladiator(newSocket, "Самнит", i, curPID);
		allGlads.push_back(newGladiator);
		qTable->Rows->Add(i, "Самнит", curPID);
		Log("Клиент " + i + " (Самнит) подключился");
		++i;
	}
	private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void ServerForm_Load(System::Object^ sender, System::EventArgs^ e) {
		srand(time(NULL));
		//Инициализация данных для клиент-сервера
		Log("Инициализация данных для клиент-сервера");
		if (WSAStartup(Dllversion, &wsaData))
		{
			//std::cout << "Ошибка" << std::endl;
		}
		addr.sin_addr.s_addr = inet_addr("127.0.0.1");
		//ofs << "Привязка IP адреса";
		addr.sin_port = htons(1111);
		addr.sin_family = AF_INET;
		sListen = socket(AF_INET, SOCK_STREAM, NULL);
		bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
		listen(sListen, SOMAXCONN);
		Log("Сервер подключен");

		//Инициализация таблицы результатов
		r = gcnew ResultsTable();
		rTable = gcnew DataTable();
		r->dataGridView1->DataSource = rTable;
		r->dataGridView1->AllowUserToAddRows = false;
		r->dataGridView1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		rTable->Columns->Add("Номер");
		rTable->Columns->Add("Тип");
		rTable->Columns->Add("Побед");
		rTable->Columns->Add("Поражен.");
		rTable->Columns->Add("Всего");
		rTable->Columns->Add("PID");
		Log("Таблица результатов создана");

		//Иницализация таблицы очереди
		q = gcnew QueueTable();
		qTable = gcnew DataTable();
		q->dataGridView1->DataSource = qTable;
		q->dataGridView1->AllowUserToAddRows = false;
		q->dataGridView1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		qTable->Columns->Add("Номер");
		qTable->Columns->Add("Тип");
		qTable->Columns->Add("PID");
		Log("Таблица очереди создана");
	}
	private: System::Void label3_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void menuStrip1_ItemClicked(System::Object^ sender, System::Windows::Forms::ToolStripItemClickedEventArgs^ e) {
	}
	private: System::Void menuStrip1_ItemClicked_1(System::Object^ sender, System::Windows::Forms::ToolStripItemClickedEventArgs^ e) {
	}
	private: System::Void backgroundWorker1_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {
	}
	private: System::Void textBox2_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label3_Click_1(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button6_Click(System::Object^ sender, System::EventArgs^ e) {
		
		if (!CanStartTheBattle)
		{
			System::Windows::Forms::DialogResult dialog = MessageBox::Show(
				"Нельзя начать битву.",
				"Ошибка",
				MessageBoxButtons::OK, MessageBoxIcon::Error);
			Log("Неудачная попытка начать битву");
		}
		else
		{
			Log("Битва началась");
			int number = 20 + rand() % 31, diff1, diff2;
			String^ text = gcnew String("");
			text += "Число для битвы: " + number.ToString() + "\n";
			int i = 1;
			do
			{
				diff1 = 1 + rand() % 3;
				diff2 = 1 + rand() % 3;
				text += i++.ToString() + " Первый гладиатор отнял от " + number.ToString() + " число " + diff1.ToString() +
					". Результат " + (number - diff1).ToString() + "\n";
				number -= diff1;
				if (number <= 0)
				{
					text += "Второй гладиатор победил! Ave, Caesar!";
					second->incVictories();
					first->incDefats();
					rTable->Clear();
					for (Gladiator* item : glads) rTable->Rows->Add(item->getNumber(),
						gcnew String(item->getType().data()),
						item->getVictories(),
						item->getDefeats(),
						item->getDefeats() + item->getVictories());
					break;
				}
				text += i++.ToString() + " Второй гладиатор отнял от " + number.ToString() + " число " + diff2.ToString() +
					". Результат " + (number - diff2).ToString() + "\n";
				number -= diff2;
				if (number <= 0)
				{
					text += "Первый гладиатор победил! Ave, Caesar!";
					first->incVictories();
					second->incDefats();
					rTable->Clear();
					for (Gladiator* item : glads) rTable->Rows->Add(item->getNumber(),
						gcnew String(item->getType().data()),
						item->getVictories(),
						item->getDefeats(),
						item->getDefeats() + item->getVictories());
				}

			} while (number > 0);
			richTextBox1->Text = text;
			Log(text);
		}
	}
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void ServerForm_FormClosing(Object^ sender, FormClosingEventArgs^ e) {
		System::Windows::Forms::DialogResult dialog = MessageBox::Show(
			"Вы действительно хотите выйти из программы?",
			"Завершение программы",
			MessageBoxButtons::YesNo, MessageBoxIcon::Question);
		if (dialog == System::Windows::Forms::DialogResult::Yes) {
			if (first && second)
			{
				Log("Клиент " + first->getNumber() + " (" + gcnew String(first->getType().data()) + ") отключился");
				Log("Клиент " + second->getNumber() + " (" + gcnew String(second->getType().data()) + ") отключился");
			}
			else if(first && !second) Log("Клиент " + first->getNumber() + " (" + gcnew String(first->getType().data()) + 
				") отключился.\n");
			else if (!first && second)Log("Клиент " + second->getNumber() + " (" + gcnew String(second->getType().data()) +
				") отключился.\n");
			e->Cancel = false;
			closesocket(sListen);
			Log("Cервер отключен\n\n---------------------------------------\n");
			system("Taskkill /IM Thracian.exe /F");
			system("Taskkill /IM Samnite.exe /F");
			Environment::Exit(0);
		}
		else e->Cancel = true;
	}
	private: System::Void button7_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}
	private: System::Void таблицаРезультатовToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		r->Show();
	}
	private: System::Void таблицаЖдущихToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		q->Show();
	}
	private: System::Void button8_Click(System::Object^ sender, System::EventArgs^ e) {
		if (allGlads.empty())
		{
			System::Windows::Forms::DialogResult dialog = MessageBox::Show(
				"Нельзя определить пару - в очереди нет ни одного клиента.",
				"Ошибка",
				MessageBoxButtons::OK, MessageBoxIcon::Error);
			Log("Неудачная попытка определить пару");
			return;
		}

		if (!first && !second) // 0 0
		{
			first = allGlads[0];
			glads.push_back((Gladiator*)first);
			allGlads.erase(allGlads.begin());
			qTable->Rows[0]->Delete();
			rTable->Rows->Add(first->getNumber(),
				gcnew String(first->getType().data()),
				first->getVictories(),
				first->getDefeats(),
				first->getVictories() + first->getDefeats(),
				first->getPID());
			textBox1->Paste(gcnew String(first->getType().data()) + " (" + gcnew String(first->getNumber().ToString()) + ")");
			Log("Первый гладиатор найден");
			if (allGlads.empty())
			{
				System::Windows::Forms::DialogResult dialog = MessageBox::Show(
					"Нашёлся только один гладиатор. Добавьте соответствующего гладиатора и повторите попытку.",
					"Предупреждение",
					MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}
			int index = 0;
			if (!strcmp(first->getType().c_str(), "Фракиец")) //Если первый был фракийцем, то ищем для него самнита и наоборот
				for (Gladiator* item : allGlads)
				{
					if (!strcmp(item->getType().c_str(), "Самнит")) break;
					++index;
				}
			else for (Gladiator* item : allGlads)
			{
				if (!strcmp(item->getType().c_str(), "Фракиец")) break;
				++index;
			}
			if (index >= allGlads.size())
			{
				System::Windows::Forms::DialogResult dialog = MessageBox::Show(
					"Нашёлся только один гладиатор. Добавьте соответствующего гладиатора и повторите попытку.",
					"Предупреждение",
					MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}
			else
			{
				second = allGlads[index];
				glads.push_back((Gladiator*)second);
				allGlads.erase(allGlads.begin() + index);
				textBox2->Clear();
				qTable->Rows[index]->Delete();
				rTable->Rows->Add(second->getNumber(),
					gcnew String(second->getType().data()),
					second->getVictories(),
					second->getDefeats(),
					second->getVictories() + second->getDefeats(),
					second->getPID());
				textBox2->Paste(gcnew String(second->getType().data()) + " (" + gcnew String(second->getNumber().ToString()) + ")");
				CanStartTheBattle = true;
				Log("Второй гладиатор найден\nПара определена");
			}
		}
		else if (first && !second) // 1 0
		{
			int index = 0;
			if (!strcmp(first->getType().c_str(), "Фракиец")) //Если первый был фракийцем, то ищем для него самнита и наоборот
				for (Gladiator* item : allGlads)
				{
					if (!strcmp(item->getType().c_str(), "Самнит")) break;
					++index;
				}
			else for (Gladiator* item : allGlads)
			{
				if (!strcmp(item->getType().c_str(), "Фракиец")) break;
				++index;
			}
			if (index >= allGlads.size())
			{
				System::Windows::Forms::DialogResult dialog = MessageBox::Show(
					"Нельзя найти подходящего оппонента",
					"Ошибка",
					MessageBoxButtons::OK, MessageBoxIcon::Error);
				Log("Неудачная попытка определить пару");
			}
			else
			{
				second = allGlads[index];
				glads.push_back((Gladiator*)second);
				allGlads.erase(allGlads.begin() + index);
				textBox2->Clear();
				qTable->Rows[index]->Delete();
				rTable->Rows->Add(second->getNumber(),
					gcnew String(second->getType().data()),
					second->getVictories(),
					second->getDefeats(),
					second->getVictories() + second->getDefeats(),
					second->getPID());
				textBox2->Paste(gcnew String(second->getType().data()) + " (" + gcnew String(second->getNumber().ToString()) + ")");
				CanStartTheBattle = true;
				Log("Второй гладиатор найден\nПара определена");
			}
		}
		else if (!first && second) // 0 1
		{
			int index = 0;
			if (!strcmp(second->getType().c_str(), "Фракиец")) //Если первый был фракийцем, то ищем для него самнита и наоборот
				for (Gladiator* item : allGlads)
				{
					if (!strcmp(item->getType().c_str(), "Самнит")) break;
					++index;
				}
			else for (Gladiator* item : allGlads)
			{
				if (!strcmp(item->getType().c_str(), "Фракиец")) break;
				++index;
			}
			if (index >= allGlads.size())
			{
				System::Windows::Forms::DialogResult dialog = MessageBox::Show(
					"Не удалось найти подходящего оппонента",
					"Ошибка",
					MessageBoxButtons::OK, MessageBoxIcon::Error);
				Log("Неудачная попытка определить пару");
			}
			else
			{
				first = allGlads[index];
				glads.push_back((Gladiator*)first);
				allGlads.erase(allGlads.begin() + index);
				textBox1->Clear();
				qTable->Rows[index]->Delete();
				rTable->Rows->Add(first->getNumber(),
					gcnew String(first->getType().data()),
					first->getVictories(),
					first->getDefeats(),
					first->getVictories() + first->getDefeats(),
					first->getPID());
				textBox1->Paste(gcnew String(first->getType().data()) + " (" + gcnew String(first->getNumber().ToString()) + ")");
				CanStartTheBattle = true;
				Log("Первый гладиатор найден.\nПара определена");
			}
		}
		else
		{
			System::Windows::Forms::DialogResult dialog = MessageBox::Show( // 1 1
				"Пара уже определена. Удалите некоторых гладиаторов, чтобы определить другую пару.",
				"Ошибка",
				MessageBoxButtons::OK, MessageBoxIcon::Error);
			Log("Неудачная попытка определить пару");
		}
	}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		if (first)
		{
			textBox1->Clear();
			CanStartTheBattle = false;
			Log("Клиент " + first->getNumber() + " (" + gcnew String(first->getType().data()) + ") отключился");
			KillProcess(first->getPID());
			first = NULL;
		}
		else
		{
			System::Windows::Forms::DialogResult dialog = MessageBox::Show(
				"Нельзя удалить первого гладиатора - его нет.",
				"Ошибка",
				MessageBoxButtons::OK, MessageBoxIcon::Error);
			Log("Неудачная попытка удалить первого клиента");
		}
	}
	private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
		if (second)
		{
			textBox2->Clear();
			CanStartTheBattle = false;
			Log("Клиент " + second->getNumber() + " (" + gcnew String(second->getType().data()) + ") отключился");
			KillProcess(second->getPID());
			second = NULL;
		}
		else
		{
			System::Windows::Forms::DialogResult dialog = MessageBox::Show(
				"Нельзя удалить второго гладиатора - его нет",
				"Ошибка",
				MessageBoxButtons::OK, MessageBoxIcon::Error);
			Log("Неудачная попытка удалить второго клиента");
		}
	}
	private: System::Void button5_Click(System::Object^ sender, System::EventArgs^ e) {
		if (second && first)
		{
			textBox1->Clear();
			textBox2->Clear();
			CanStartTheBattle = false;
			Log("Клиент " + first->getNumber() + " (" + gcnew String(first->getType().data()) + ") отключился");
			Log("Клиент " + second->getNumber() + " (" + gcnew String(second->getType().data()) + ") отключился");
			KillProcess(first->getPID());
			KillProcess(second->getPID());
			first = NULL;
			second = NULL;
		}
		else
		{
			System::Windows::Forms::DialogResult dialog = MessageBox::Show(
				"Нельзя удалить сразу обоих.",
				"Ошибка",
				MessageBoxButtons::OK, MessageBoxIcon::Error);
			Log("Неудачная попытка удалить обоих клиентов");
		}
	}
	private: System::Void richTextBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
};
}
