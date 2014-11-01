@Rem 存在洞的多边形，必须使用两个path表示，内部逆时针，外部顺时针
clipper.exe subj.txt clip.txt UNION EVENODD EVENODD 1 30