#pragma once
#include <list>
#include "DeepNeyroset.h"
#include <vector>
#include <fstream>
#include <iostream>


namespace DrawNums {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	private:
		System::Windows::Forms::PictureBox^ recr;
		bool flag;
		System::Windows::Forms::TextBox^  textBox1;
		System::Windows::Forms::Button^  button1;
		System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
		System::Windows::Forms::Button^  button2;
		Graphics^ gg;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
			 Deepnetwork* N;
	public:
		MyForm(void)
		{
			N = new Deepnetwork();
			flag = false;
			InitializeComponent();
			recr->Image = Image::FromFile("Bitmap.bmp");
			gg = Graphics::FromImage(recr->Image);
			
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete N;
				delete components;
			}
		}

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->recr = (gcnew System::Windows::Forms::PictureBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->recr))->BeginInit();
			this->tableLayoutPanel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// recr
			// 
			this->recr->BackColor = System::Drawing::SystemColors::Window;
			this->recr->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->recr->Location = System::Drawing::Point(49, 96);
			this->recr->Name = L"recr";
			this->recr->Size = System::Drawing::Size(280, 280);
			this->recr->TabIndex = 0;
			this->recr->TabStop = false;
			this->recr->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::button1_Click);
			this->recr->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::button2_Click);
			this->recr->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::button3_Click);
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox1->Location = System::Drawing::Point(402, 96);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(328, 29);
			this->textBox1->TabIndex = 1;
			// 
			// button1
			// 
			this->button1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->button1->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->button1->Location = System::Drawing::Point(3, 3);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(194, 40);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Распознавание";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 1;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel1->Controls->Add(this->button1, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->button2, 0, 1);
			this->tableLayoutPanel1->Location = System::Drawing::Point(478, 273);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 2;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(200, 100);
			this->tableLayoutPanel1->TabIndex = 2;
			// 
			// button2
			// 
			this->button2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->button2->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->button2->Location = System::Drawing::Point(3, 53);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(194, 40);
			this->button2->TabIndex = 0;
			this->button2->Text = L"Очистка ";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button5_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(494, 69);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(169, 24);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Ответ нейросети";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(145, 77);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(84, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Нарисуй цифру";
			// 
			// MyForm
			// 
			this->AcceptButton = this->button1;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Control;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->CancelButton = this->button1;
			this->ClientSize = System::Drawing::Size(837, 535);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->recr);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Name = L"MyForm";
			this->Text = L"DrawNums";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->recr))->EndInit();
			this->tableLayoutPanel1->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}

#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		flag = true;
	}
	private: System::Void button2_Click(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		if (flag) {
			gg->FillEllipse(System::Drawing::Brushes::Black, e->X, e->Y,25,25);
			recr->Refresh();
		}
	}
	private: System::Void button3_Click(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		flag = false;
	}

	private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
		std::ofstream out("Image.txt");
		out << 28 << ' ' << 28 << std::endl;
		Bitmap o(recr->Image, 280, 280);
		int a4;
		for (int i = 0; i < 28; i++)
		{
			for (int j = 0; j < 28; j++)
			{
				a4 = 0;
				for (int ii = i * 10; ii < (i + 1) * 10; ii++) {
					for (int jj = j*10; jj < (j + 1) * 10; jj++) {
						if (o.GetPixel(jj, ii) == Color::FromArgb(0, 0, 0)) {
							a4++;
						}
					}
				}
				if (a4 > 30) {
					out << std::setw(2) << 1 << ' ';
				}
				else {
					out << std::setw(2) << -1 << ' ';
				}
			}
			out << std::endl;
		}

		textBox1->Text = Convert::ToString(N->Neyroset());
	}
	private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
		gg->FillRectangle(SystemBrushes::Window, 0, 0, 280, 280);
		recr->Refresh();
		std::ofstream out("Image.txt", 0);
		textBox1->Text = "";
	}

	private: System::Void flowLayoutPanel1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
	}
private: System::Void pictureBox1_Click(System::Object^  sender, System::EventArgs^  e) {
	}
};
}

