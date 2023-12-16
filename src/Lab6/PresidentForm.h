#pragma once

#include "PresidentI.h"

namespace Lab6 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for PresidentForm
	/// </summary>
	public ref class PresidentForm : public System::Windows::Forms::Form
	{
	private:
		PresidentI* president;

		void setCardsClickHandlers();
		Void Card_Click(Object^ sender, EventArgs^ e);
	public:
		PresidentForm(void);

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~PresidentForm();

	private: System::Windows::Forms::FlowLayoutPanel^ humanCards;
	private: System::Windows::Forms::FlowLayoutPanel^ AI1Cards;
	private: System::Windows::Forms::FlowLayoutPanel^ AI2Cards;
	private: System::Windows::Forms::FlowLayoutPanel^ AI3Cards;
	private: System::Windows::Forms::FlowLayoutPanel^ cardsOnDesk;

	protected:

	protected:

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
			this->humanCards = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->AI1Cards = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->AI2Cards = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->AI3Cards = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->cardsOnDesk = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->SuspendLayout();
			// 
			// humanCards
			// 
			this->humanCards->Location = System::Drawing::Point(148, 797);
			this->humanCards->Name = L"humanCards";
			this->humanCards->Size = System::Drawing::Size(1628, 261);
			this->humanCards->TabIndex = 0;
			// 
			// AI1Cards
			// 
			this->AI1Cards->FlowDirection = System::Windows::Forms::FlowDirection::TopDown;
			this->AI1Cards->Location = System::Drawing::Point(12, 12);
			this->AI1Cards->Name = L"AI1Cards";
			this->AI1Cards->Size = System::Drawing::Size(130, 1031);
			this->AI1Cards->TabIndex = 1;
			// 
			// AI2Cards
			// 
			this->AI2Cards->Location = System::Drawing::Point(148, 12);
			this->AI2Cards->Name = L"AI2Cards";
			this->AI2Cards->Size = System::Drawing::Size(1628, 173);
			this->AI2Cards->TabIndex = 2;
			// 
			// AI3Cards
			// 
			this->AI3Cards->FlowDirection = System::Windows::Forms::FlowDirection::TopDown;
			this->AI3Cards->Location = System::Drawing::Point(1782, 12);
			this->AI3Cards->Name = L"AI3Cards";
			this->AI3Cards->Size = System::Drawing::Size(130, 1031);
			this->AI3Cards->TabIndex = 3;
			// 
			// cardsOnDesk
			// 
			this->cardsOnDesk->Location = System::Drawing::Point(633, 374);
			this->cardsOnDesk->Name = L"cardsOnDesk";
			this->cardsOnDesk->Size = System::Drawing::Size(735, 228);
			this->cardsOnDesk->TabIndex = 4;
			// 
			// PresidentForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::OliveDrab;
			this->ClientSize = System::Drawing::Size(1924, 1055);
			this->Controls->Add(this->cardsOnDesk);
			this->Controls->Add(this->AI3Cards);
			this->Controls->Add(this->AI2Cards);
			this->Controls->Add(this->AI1Cards);
			this->Controls->Add(this->humanCards);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"PresidentForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"President";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->ResumeLayout(false);

		}
#pragma endregion
	};
}
