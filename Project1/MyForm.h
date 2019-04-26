#pragma once
#include <list>
namespace DrawNums {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;

	/// <summary>
	/// ������ ��� MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	private:
	System::Windows::Forms::Button^  button1;
	System::Windows::Forms::PictureBox^ recr;
	bool flag;
	Graphics^ gg;
	Rectangle^ r;
	Bitmap image;

	public:
		MyForm(void):image(300,500)
		{

			flag = false;
			InitializeComponent();
			recr->Image =(Image^&) image;
			gg = Graphics::FromImage((Image^&)image);

		}

	protected:
		/// <summary>
		/// ���������� ��� ������������ �������.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// ������������ ���������� ������������.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// ��������� ����� ��� ��������� ������������ � �� ��������� 
		/// ���������� ����� ������ � ������� ��������� ����.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->recr = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->recr))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->button1->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->button1->Location = System::Drawing::Point(576, 406);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(100, 40);
			this->button1->TabIndex = 0;
			this->button1->Text = L"�������������";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// recr
			// 
			this->recr->BackColor = System::Drawing::SystemColors::Window;
			//this->recr->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"recr.BackgroundImage")));
			this->recr->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->recr->Location = System::Drawing::Point(10, 10);
			this->recr->Name = L"recr";
			this->recr->Size = System::Drawing::Size(300, 500);
			this->recr->TabIndex = 0;
			this->recr->TabStop = false;
			this->recr->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::button1_Click);
			this->recr->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::button2_Click);
			this->recr->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::button3_Click);
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
			this->Controls->Add(this->button1);
			this->Controls->Add(this->recr);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Name = L"MyForm";
			this->Text = L"Form1";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->recr))->EndInit();
			this->ResumeLayout(false);

		}

#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		flag = true;
	}
	private: System::Void button2_Click(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		if (flag) {
			gg->FillEllipse(System::Drawing::Brushes::Black, e->X, e->Y,10,10);
		}
	}
	private: System::Void button3_Click(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		flag = false;
	}

	private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
		Bitmap o(recr->Width, recr->Height, gg);
		o.Save("E:\\CNN_ITMM\\Project1\\Image.bmp", );
		long int a4 = 0;
		for (int i = 0; i < recr->Height; i++)
		{
			for (int h = 0; h < recr->Width; h++)
			{
				if (o.GetPixel(h, i) == Color::Black)
					a4++;
			}
		}
		button1->Text = Convert::ToString(a4);
	}
	};
}