clear
close all

%以ReviewID作为主键
hair_dryer=readtable('C:\Users\mashed potato\Desktop\MCM\2020_Weekend2_Problems\Problem_C_Data\hair_dryer.xlsx','ReadRowNames',true);
micro_wave=readtable('C:\Users\mashed potato\Desktop\MCM\2020_Weekend2_Problems\Problem_C_Data\micro_wave.xlsx','ReadRowNames',true);
pacifier=readtable('C:\Users\mashed potato\Desktop\MCM\2020_Weekend2_Problems\Problem_C_Data\pacifier.xlsx','ReadRowNames',true);

hair_pre=readtable('C:\Users\mashed potato\Desktop\MCM\2020_Weekend2_Problems\Problem_C_Data\hair_preprocess.xlsx','ReadRowNames',true);
micro_pre=readtable('C:\Users\mashed potato\Desktop\MCM\2020_Weekend2_Problems\Problem_C_Data\micro_preprocess.xlsx','ReadRowNames',true);
pacifier_pre=readtable('C:\Users\mashed potato\Desktop\MCM\2020_Weekend2_Problems\Problem_C_Data\pacifier_preprocess.xlsx','ReadRowNames',true);

opts = detectImportOptions('C:\Users\mashed potato\Desktop\MCM\2020_Weekend2_Problems\Problem_C_Data\hair_pro5.xlsx');
opts.Sheet='Sheet1';
hair_pro=readtable('C:\Users\mashed potato\Desktop\MCM\2020_Weekend2_Problems\Problem_C_Data\hair_pro5.xlsx',opts,'ReadRowNames',true);
save('C:\Users\mashed potato\Desktop\MCM\data\data');