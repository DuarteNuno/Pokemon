class Slot
{
	public:
		Jogador j;
	 	int i;
	 	
	public:
		void guardar();
		bool carregar(int i);	 	
		int  procuraSlot();
	
		Slot(int ind);
		Slot();
	
};
