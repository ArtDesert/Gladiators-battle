#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
#include <vector>
#include <thread>
#include <time.h>
#include <string>
#include <mutex>
#include <conio.h>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)
#include <winsock2.h>
namespace Samnite {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	WSAData wsaData;
	WORD Dllversion = MAKEWORD(2, 1);
	SOCKADDR_IN addr;
	int sizeofAddr = sizeof(addr);
	SOCKET connection;

	/// <summary>
	/// Сводка для SamniteForm
	/// </summary>
	public ref class SamniteForm : public System::Windows::Forms::Form
	{
	public:
		SamniteForm(void)
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
		~SamniteForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::RichTextBox^ richTextBox1;
	private: System::Windows::Forms::Label^ label1;
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
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// richTextBox1
			// 
			this->richTextBox1->BackColor = System::Drawing::SystemColors::Info;
			this->richTextBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->richTextBox1->Cursor = System::Windows::Forms::Cursors::Arrow;
			this->richTextBox1->Enabled = false;
			this->richTextBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->richTextBox1->Location = System::Drawing::Point(12, 49);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(460, 150);
			this->richTextBox1->TabIndex = 6;
			this->richTextBox1->Text = L"";
			this->richTextBox1->TextChanged += gcnew System::EventHandler(this, &SamniteForm::richTextBox1_TextChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->ForeColor = System::Drawing::Color::Teal;
			this->label1->Location = System::Drawing::Point(42, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(402, 24);
			this->label1->TabIndex = 7;
			this->label1->Text = L"Добро пожаловать на гладиаторские игры!";
			this->label1->Click += gcnew System::EventHandler(this, &SamniteForm::label1_Click);
			// 
			// SamniteForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(484, 211);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->richTextBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"SamniteForm";
			this->Text = L" Самнит";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &SamniteForm::SamniteForm_FormClosing);
			this->Load += gcnew System::EventHandler(this, &SamniteForm::SamniteForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void SamniteForm_Load(System::Object^ sender, System::EventArgs^ e) {
		addr.sin_addr.s_addr = inet_addr("127.0.0.1");
		addr.sin_port = htons(1111);
		addr.sin_family = AF_INET;
		if (WSAStartup(Dllversion, &wsaData))
		{
		}
		connection = socket(AF_INET, SOCK_STREAM, NULL);
		if (connect(connection, (SOCKADDR*)&addr, sizeof(addr)) != 0)
		{
		} 
		char c;
		recv(connection, &c, sizeof(c), NULL);
		String^ str = "Вы подключились к гладиаторским играм!\nВаш номер: " + char(c - 48) + ", ваш тип: Самнит\n";
		richTextBox1->Text = str;
	}
	private: System::Void SamniteForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
		/*
		System::Windows::Forms::DialogResult dialog = MessageBox::Show(
			"Вы действительно хотите выйти из программы?",
			"Завершение программы",
			MessageBoxButtons::YesNo, MessageBoxIcon::Warning);
		if (dialog == System::Windows::Forms::DialogResult::Yes) {
			e->Cancel = false;
			closesocket(connection);
			WSACleanup(); //Деиницилизация библиотеки Winsock
			Environment::Exit(0);
		}
		else e->Cancel = true;
		*/
		e->Cancel = false;
		closesocket(connection);
		WSACleanup(); //Деиницилизация библиотеки Winsock
		Environment::Exit(0);
	}
	private: System::Void richTextBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}
