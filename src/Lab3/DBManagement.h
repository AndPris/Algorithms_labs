#pragma once

#include "../Lab3_code/B_Tree.h"
#include "Data_validators.h"
#include <string>
namespace Lab3 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for DBManagement
	/// </summary>
	public ref class DBManagement : public System::Windows::Forms::Form
	{
	public:
		DBManagement(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

		DBManagement(std::string file_path_to_save);
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~DBManagement()
		{
			if (components)
			{
				delete components;
			}

			delete tree;
			delete file_path_to_save;
		}
	private:
		int minimum_degree;
		std::string* file_path_to_save;
		BTree* tree;
		void display();
		void remove_row(int key);
		void edit_row(int key, char* data);

		void disable_edit_delete_search();
		void enable_edit_delete_search();

	private: System::Windows::Forms::DataGridView^ data_table;
	protected:

	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Key;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Data;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ insertion_btn;
	private: System::Windows::Forms::TextBox^ key_to_insert;
	private: System::Windows::Forms::TextBox^ data_to_insert;
	private: System::Windows::Forms::TextBox^ key_to_delete;
	private: System::Windows::Forms::Button^ deletion_btn;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TextBox^ new_data;
	private: System::Windows::Forms::TextBox^ key_to_edit;
	private: System::Windows::Forms::Button^ editing_btn;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::TextBox^ key_to_find;
	private: System::Windows::Forms::Button^ find_btn;
	private: System::Windows::Forms::Label^ label8;
	protected:



	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->data_table = (gcnew System::Windows::Forms::DataGridView());
			this->Key = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Data = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->insertion_btn = (gcnew System::Windows::Forms::Button());
			this->key_to_insert = (gcnew System::Windows::Forms::TextBox());
			this->data_to_insert = (gcnew System::Windows::Forms::TextBox());
			this->key_to_delete = (gcnew System::Windows::Forms::TextBox());
			this->deletion_btn = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->new_data = (gcnew System::Windows::Forms::TextBox());
			this->key_to_edit = (gcnew System::Windows::Forms::TextBox());
			this->editing_btn = (gcnew System::Windows::Forms::Button());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->key_to_find = (gcnew System::Windows::Forms::TextBox());
			this->find_btn = (gcnew System::Windows::Forms::Button());
			this->label8 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->data_table))->BeginInit();
			this->SuspendLayout();
			// 
			// data_table
			// 
			this->data_table->AllowUserToAddRows = false;
			this->data_table->BackgroundColor = System::Drawing::SystemColors::ButtonHighlight;
			this->data_table->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->data_table->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) { this->Key, this->Data });
			this->data_table->GridColor = System::Drawing::SystemColors::ButtonHighlight;
			this->data_table->Location = System::Drawing::Point(-1, 183);
			this->data_table->Name = L"data_table";
			this->data_table->RowHeadersVisible = false;
			this->data_table->RowHeadersWidth = 51;
			this->data_table->RowTemplate->Height = 24;
			this->data_table->Size = System::Drawing::Size(1008, 354);
			this->data_table->TabIndex = 0;
			// 
			// Key
			// 
			this->Key->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			this->Key->HeaderText = L"Key";
			this->Key->MinimumWidth = 6;
			this->Key->Name = L"Key";
			this->Key->ReadOnly = true;
			// 
			// Data
			// 
			this->Data->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			this->Data->HeaderText = L"Data";
			this->Data->MinimumWidth = 6;
			this->Data->Name = L"Data";
			this->Data->ReadOnly = true;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(85, 16);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Key to insert :";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 35);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(91, 16);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Data to insert :";
			// 
			// insertion_btn
			// 
			this->insertion_btn->Location = System::Drawing::Point(72, 63);
			this->insertion_btn->Name = L"insertion_btn";
			this->insertion_btn->Size = System::Drawing::Size(102, 40);
			this->insertion_btn->TabIndex = 3;
			this->insertion_btn->Text = L"Insert";
			this->insertion_btn->UseVisualStyleBackColor = true;
			this->insertion_btn->Click += gcnew System::EventHandler(this, &DBManagement::insertion_btn_Click);
			// 
			// key_to_insert
			// 
			this->key_to_insert->Location = System::Drawing::Point(103, 6);
			this->key_to_insert->MaxLength = 6;
			this->key_to_insert->Name = L"key_to_insert";
			this->key_to_insert->Size = System::Drawing::Size(130, 22);
			this->key_to_insert->TabIndex = 4;
			// 
			// data_to_insert
			// 
			this->data_to_insert->Location = System::Drawing::Point(103, 35);
			this->data_to_insert->MaxLength = 30;
			this->data_to_insert->Name = L"data_to_insert";
			this->data_to_insert->Size = System::Drawing::Size(130, 22);
			this->data_to_insert->TabIndex = 5;
			// 
			// key_to_delete
			// 
			this->key_to_delete->Location = System::Drawing::Point(354, 18);
			this->key_to_delete->MaxLength = 6;
			this->key_to_delete->Name = L"key_to_delete";
			this->key_to_delete->Size = System::Drawing::Size(130, 22);
			this->key_to_delete->TabIndex = 9;
			// 
			// deletion_btn
			// 
			this->deletion_btn->Location = System::Drawing::Point(323, 63);
			this->deletion_btn->Name = L"deletion_btn";
			this->deletion_btn->Size = System::Drawing::Size(102, 40);
			this->deletion_btn->TabIndex = 8;
			this->deletion_btn->Text = L"Delete";
			this->deletion_btn->UseVisualStyleBackColor = true;
			this->deletion_btn->Click += gcnew System::EventHandler(this, &DBManagement::deletion_btn_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(257, 21);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(91, 16);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Key to delete :";
			// 
			// new_data
			// 
			this->new_data->Location = System::Drawing::Point(603, 32);
			this->new_data->MaxLength = 30;
			this->new_data->Name = L"new_data";
			this->new_data->Size = System::Drawing::Size(130, 22);
			this->new_data->TabIndex = 15;
			// 
			// key_to_edit
			// 
			this->key_to_edit->Location = System::Drawing::Point(603, 3);
			this->key_to_edit->MaxLength = 6;
			this->key_to_edit->Name = L"key_to_edit";
			this->key_to_edit->Size = System::Drawing::Size(130, 22);
			this->key_to_edit->TabIndex = 14;
			// 
			// editing_btn
			// 
			this->editing_btn->Location = System::Drawing::Point(572, 60);
			this->editing_btn->Name = L"editing_btn";
			this->editing_btn->Size = System::Drawing::Size(102, 40);
			this->editing_btn->TabIndex = 13;
			this->editing_btn->Text = L"Edit";
			this->editing_btn->UseVisualStyleBackColor = true;
			this->editing_btn->Click += gcnew System::EventHandler(this, &DBManagement::editing_btn_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(512, 32);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(70, 16);
			this->label5->TabIndex = 12;
			this->label5->Text = L"New data :";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(512, 6);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(75, 16);
			this->label6->TabIndex = 11;
			this->label6->Text = L"Key to edit :";
			// 
			// key_to_find
			// 
			this->key_to_find->Location = System::Drawing::Point(842, 18);
			this->key_to_find->MaxLength = 6;
			this->key_to_find->Name = L"key_to_find";
			this->key_to_find->Size = System::Drawing::Size(130, 22);
			this->key_to_find->TabIndex = 19;
			// 
			// find_btn
			// 
			this->find_btn->Location = System::Drawing::Point(822, 63);
			this->find_btn->Name = L"find_btn";
			this->find_btn->Size = System::Drawing::Size(102, 40);
			this->find_btn->TabIndex = 18;
			this->find_btn->Text = L"Find";
			this->find_btn->UseVisualStyleBackColor = true;
			this->find_btn->Click += gcnew System::EventHandler(this, &DBManagement::find_btn_Click);
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(762, 21);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(74, 16);
			this->label8->TabIndex = 16;
			this->label8->Text = L"Key to find :";
			// 
			// DBManagement
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1004, 536);
			this->Controls->Add(this->key_to_find);
			this->Controls->Add(this->find_btn);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->new_data);
			this->Controls->Add(this->key_to_edit);
			this->Controls->Add(this->editing_btn);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->key_to_delete);
			this->Controls->Add(this->deletion_btn);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->data_to_insert);
			this->Controls->Add(this->key_to_insert);
			this->Controls->Add(this->insertion_btn);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->data_table);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"DBManagement";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"DBManagement";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->data_table))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: Void insertion_btn_Click(Object^ sender, EventArgs^ e);
			Void deletion_btn_Click(Object^ sender, EventArgs^ e);
			Void editing_btn_Click(Object^ sender, EventArgs^ e);
			Void find_btn_Click(Object^ sender, EventArgs^ e);
};
}
