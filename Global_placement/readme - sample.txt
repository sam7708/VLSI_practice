1. �Ǹ��G
2. �m�W�G
3. �ϥΤ��{���y���G< C++ >
4. �ϥΤ��sĶ���G< GNU g++ >
5. �ɮ����Y�覡: <tar cvfz A15.tar.gz A15>
6. �U�ɮ׻����G
	 A60/Source/Explode : �¤�r�D�{��
	 A60/Source/Verify  : �¤�r���ҵ{��
	 A60/Source/Visulize : ����ø�ϵ{���]�ۮe��WindowsXP�BWindows2000���^
	 A60/Report.doc �G �{�����i

7. �sĶ�覡�����G        	
   �D�{���GA60/Source/Explode
	 �Цb�D�{�����ؿ��U�A��Jmake���O�A�Y�i�����sĶ�A
	 ( Makefile����U�� Optimize ���O�� -O2
	 �Y�O�n��� -O �ШϥΦP��ƧX�U�� Makefile2 )
	 �b�D�{�����ؿ��U�|���ͤ@�ӦW�� a.out ��������
	 �p�G�n���s�sĶ�A�Х����� make clean �A����@�� make
	
   ���ҵ{���G�P"�D�{��"

   ����ø�ϵ{���G����������ø�����ҵ{���bA60/Source/Visualize/Release���w��
	 �[Visualize.exe�������ɡC�b�������x�W�I����U�����ɡA�Y�i
	 �}��ø�ϵ{���C�Y�n���s�sĶ�A�Х�Visual Studio.NET�}��Source/Visualize/
	 Visulize.sln�ɮסC�T�wActive Configuration��"Release"����A
	 ���Build��Build Solution�A�i��sĶ�C�bRelease�ؿ��U�|���Ͱ����ɡC

           . . . . . .  
8. ����B�ϥΤ覡�����G
   �D�{���G
   �sĶ������A�b�ɮץؿ��U�|���ͤ@�� a.out ��������
   �����ɪ��R�O�榡���G
   ./a.out <input file name> <top cell name>
   �Ҧp�G�n�� V07Q.dat �� cell V07Q �@explode
   �h�b�R�O���ܤU��J
   ./a.out V07Q.dat V07Q

   ���ҵ{���G�����ɦW��verify�A�R�O�榡�P�D�{���ۦP
           . . . . . .         
9. ���浲�G�����]�������浲�G���[�ݤ�k�A�θ����U���ƾڵ��^�G
   �D�{���G
	 �D�{������ɷ|�b console ��X�ثe���檺�B�J�B���h����W�١B
	 �̤j���h�ơB����G���X��ϧμơB�P�U�B�J������ɶ��C
	 ��X�ɬ��b���ؿ��U�� result.dat �A �t�~�|��X���@ explode
	 �ӳ��h���󦳰ѦҨ쪺 physical layout �� original.dat
	 �Ҧp�G���� ./a.out V07Q.dat V07Q ��Aconsole �|��X
	
 	 Program initializing
	 Top cell name: V07Q						-- ���h����W��
	 Max hierarchical level: 12					-- �̤j���h��
	 Real rects count = 398863					-- �X��ϧμ�
	 Start of overlapping checking
	 End of overlapping checking
	 Start of exploding
	 Finishing program and writing result
	
	
	 Program initialization spends 0.420000 seconds			-- �U���B�J�p��
	 Overlapping graph construction spends 65.780000 secnods
	 Removing of hierarchical overlapping spends 0.700000 secnods
	 Finishing program and writing results spends 2.600000 seconds

	 Total program time = 69.500000 seconds				-- �{���`����ɶ�



       

