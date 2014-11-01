@Rem http://zh.wikipedia.org/wiki/MS-DOS%E5%91%BD%E4%BB%A4%E5%88%97%E8%A1%A8

@Rem 存在洞的多边形，必须使用两个path表示
@Rem clip.txt中两个path都是顺时针方向存储
clipper.exe subj.txt clip.txt UNION EVENODD EVENODD 1 30

del solution1.svg
ren solution.svg solution1.svg

@Rem clip-oc.txt中外部path为逆时针，内部为顺时针
clipper.exe subj.txt clip-oc.txt UNION EVENODD EVENODD 1 30
del solution2.svg
ren solution.svg solution2.svg

@Rem clip-ic.txt中外部path为顺时针，内部为逆时针
clipper.exe subj.txt clip-ic.txt UNION EVENODD EVENODD 1 30
del solution3.svg
ren solution.svg solution3.svg

@Rem clip-ic_oc.txt中两个path都是逆时针方向存储
clipper.exe subj.txt clip-ic_oc.txt UNION EVENODD EVENODD 1 30

@Rem 设置字符串 set info=1,1 \n 2,2
@Rem 打印字符串，并写到2文件中 echo %info% > 2