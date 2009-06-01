<?xml version='1.0' encoding='ISO-8859-1' standalone='yes' ?>
<tagfile>
  <compound kind="class">
    <name>Chromosome</name>
    <filename>classChromosome.html</filename>
    <member kind="function">
      <type></type>
      <name>Chromosome</name>
      <anchorfile>classChromosome.html</anchorfile>
      <anchor>7eb065b8aa3799e0cca4608e2d3606b7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QPFWPVector</type>
      <name>createNew</name>
      <anchorfile>classChromosome.html</anchorfile>
      <anchor>8e2c2536f795ba81262d3e40afb37db4</anchor>
      <arglist>(QPFWPVector points)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setElements</name>
      <anchorfile>classChromosome.html</anchorfile>
      <anchor>b36aaa86e43f640d15c3ab910bab985a</anchor>
      <arglist>(QPFWPVector points, bool random)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setFitness</name>
      <anchorfile>classChromosome.html</anchorfile>
      <anchor>a3b78b92b3ec3d13ae81bd796818c9d0</anchor>
      <arglist>(double fit)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>calcRouteLength</name>
      <anchorfile>classChromosome.html</anchorfile>
      <anchor>09f95d91e6bab0e746919bca5437ff5b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getRouteLength</name>
      <anchorfile>classChromosome.html</anchorfile>
      <anchor>1167ad0614f1b741978f66d2d8764328</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>QPFWPVector</type>
      <name>elements</name>
      <anchorfile>classChromosome.html</anchorfile>
      <anchor>7077b57579c6307a729f7ee910522251</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>MySize</name>
      <anchorfile>classChromosome.html</anchorfile>
      <anchor>a34f6a62e9bca551c63eec0d8e7fb96d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>routeLength</name>
      <anchorfile>classChromosome.html</anchorfile>
      <anchor>d1ed30c04cb0647dbe893763d5e5872b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>fitness</name>
      <anchorfile>classChromosome.html</anchorfile>
      <anchor>84689d429c53bee462e0d4c7b3e44294</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>GCode</name>
    <filename>classGCode.html</filename>
    <member kind="function">
      <type></type>
      <name>GCode</name>
      <anchorfile>classGCode.html</anchorfile>
      <anchor>6b8b94094856d9cf2b9ef6a453512cdd</anchor>
      <arglist>(QFile *file)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>writeHeader</name>
      <anchorfile>classGCode.html</anchorfile>
      <anchor>0b724a4e28d4e3b30fc13a3e0d1bd5fb</anchor>
      <arglist>(QString filename)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>writeClosedLoop</name>
      <anchorfile>classGCode.html</anchorfile>
      <anchor>2e94c10714854752509ac78adffa93b3</anchor>
      <arglist>(QPFWPVector closedLoop)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>writeEnd</name>
      <anchorfile>classGCode.html</anchorfile>
      <anchor>86f9574bafb8d26fd2a2557f2819d581</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>comment</name>
      <anchorfile>classGCode.html</anchorfile>
      <anchor>54b52aa80d6d30399420fcca65a13fae</anchor>
      <arglist>(QString comment)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addLineNumber</name>
      <anchorfile>classGCode.html</anchorfile>
      <anchor>06edbe0be4c767ca5fcf579c1c01c469</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>home</name>
      <anchorfile>classGCode.html</anchorfile>
      <anchor>ed2754ac215a5c4811e6840a40ee1731</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>rapidMove</name>
      <anchorfile>classGCode.html</anchorfile>
      <anchor>dad90a21014627062bbe68bbe14cf838</anchor>
      <arglist>(QPointF p, qreal Z=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>feedRateMove</name>
      <anchorfile>classGCode.html</anchorfile>
      <anchor>e2e5b06f53a98417aa337c0f144c33ac</anchor>
      <arglist>(QPointF p, qreal Z=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ArcCut</name>
      <anchorfile>classGCode.html</anchorfile>
      <anchor>de7570bba9ac2d5c7820154b1e02f877</anchor>
      <arglist>(QPointF p, qreal Z, QPointF p2, qreal radius, bool cw=true)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>appendCode</name>
      <anchorfile>classGCode.html</anchorfile>
      <anchor>a456b975fc4792b9d2f05504ab42cde6</anchor>
      <arglist>(QString code, QString value=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>appendNumCode</name>
      <anchorfile>classGCode.html</anchorfile>
      <anchor>77a6c967522542ab8d979faff489e41b</anchor>
      <arglist>(QString code, qreal value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>cartidgeReturn</name>
      <anchorfile>classGCode.html</anchorfile>
      <anchor>37b62021e508182a8f5a6a36d73aa5eb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setLastPos</name>
      <anchorfile>classGCode.html</anchorfile>
      <anchor>eaa95999ee19cdefda206a323881800f</anchor>
      <arglist>(QPointF val)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setTrans</name>
      <anchorfile>classGCode.html</anchorfile>
      <anchor>c4861f0a4d0987347f9f983413f3d894</anchor>
      <arglist>(QTransform tr)</arglist>
    </member>
    <member kind="variable">
      <type>QTransform</type>
      <name>partTrans</name>
      <anchorfile>classGCode.html</anchorfile>
      <anchor>0e7a32abbfe99a1387bbbdf16c7bd043</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Lead</name>
    <filename>classLead.html</filename>
    <member kind="function">
      <type></type>
      <name>Lead</name>
      <anchorfile>classLead.html</anchorfile>
      <anchor>2546113273193f91e782d9959e5f7627</anchor>
      <arglist>(Loop *loop)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Lead</name>
      <anchorfile>classLead.html</anchorfile>
      <anchor>949c4178e643b79425436ad1f255789a</anchor>
      <arglist>(Loop *loop, int j)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Lead</name>
      <anchorfile>classLead.html</anchorfile>
      <anchor>0b713685db3e12033e93ef70eb205af6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>paint</name>
      <anchorfile>classLead.html</anchorfile>
      <anchor>07dc28b256020ec2489400bedb89e825</anchor>
      <arglist>(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)</arglist>
    </member>
    <member kind="function">
      <type>QRectF</type>
      <name>boundingRect</name>
      <anchorfile>classLead.html</anchorfile>
      <anchor>6dd98806b6fd0eaa66cbe6a38ef283d2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QPainterPath</type>
      <name>shape</name>
      <anchorfile>classLead.html</anchorfile>
      <anchor>4dcf90d0e7a751034e619721aa406903</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>type</name>
      <anchorfile>classLead.html</anchorfile>
      <anchor>30fc71bb475d89ad0f2570da913c4f9a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setEdge</name>
      <anchorfile>classLead.html</anchorfile>
      <anchor>9b303d3a9f584915f2e2b4ee8481255c</anchor>
      <arglist>(Edge *edge)</arglist>
    </member>
    <member kind="variable">
      <type>QRectF</type>
      <name>myBoundingRect</name>
      <anchorfile>classLead.html</anchorfile>
      <anchor>6533c56a4e95001e28d41ad57ec6aebd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Lead::leadTypes</type>
      <name>leadType</name>
      <anchorfile>classLead.html</anchorfile>
      <anchor>5ce198a5f7bbce58aa4656c0fb628a05</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Loop *</type>
      <name>myLoop</name>
      <anchorfile>classLead.html</anchorfile>
      <anchor>bd853d78732939a94d154fff23adf2c3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QPointFWithParent *</type>
      <name>myPos</name>
      <anchorfile>classLead.html</anchorfile>
      <anchor>4f6ba6a41e2087f6b0163266a58dad44</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QPointFWithParent</type>
      <name>leadTouch</name>
      <anchorfile>classLead.html</anchorfile>
      <anchor>3d4b2124d43ee44531b44512ecca5be2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Edge *</type>
      <name>myEdge</name>
      <anchorfile>classLead.html</anchorfile>
      <anchor>1c69dd0341250b7b1e948dec89cc9d3f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QGraphicsLineItem</type>
      <name>linkLine</name>
      <anchorfile>classLead.html</anchorfile>
      <anchor>a720fceb03b6a25eb0687309deeca2ac</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QRectF</type>
      <name>laserRect</name>
      <anchorfile>classLead.html</anchorfile>
      <anchor>ddd56bbc9e6075cf7ca4b9ce19bdb4a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>leadRadius</name>
      <anchorfile>classLead.html</anchorfile>
      <anchor>19af9e3923c4f998fcde8a57919c4966</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QSettings</type>
      <name>settings</name>
      <anchorfile>classLead.html</anchorfile>
      <anchor>6b1a027849cd5d6cb1842778105ab71d</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>QVariant</type>
      <name>itemChange</name>
      <anchorfile>classLead.html</anchorfile>
      <anchor>aa4fddef357112d7af5a96ed186bd634</anchor>
      <arglist>(GraphicsItemChange change, const QVariant &amp;value)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>mousePressEvent</name>
      <anchorfile>classLead.html</anchorfile>
      <anchor>5ce184647ace548851461bd98f8e1b46</anchor>
      <arglist>(QGraphicsSceneMouseEvent *event)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>mouseReleaseEvent</name>
      <anchorfile>classLead.html</anchorfile>
      <anchor>27f5d5f1d434f165fae46dc41e936c35</anchor>
      <arglist>(QGraphicsSceneMouseEvent *event)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>mouseMoveEvent</name>
      <anchorfile>classLead.html</anchorfile>
      <anchor>ed17aeb0c78828cbc17b3e18c835111f</anchor>
      <arglist>(QGraphicsSceneMouseEvent *event)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Loop</name>
    <filename>classLoop.html</filename>
    <member kind="function">
      <type></type>
      <name>Loop</name>
      <anchorfile>classLoop.html</anchorfile>
      <anchor>05fc41ad4d36c29dea20704a9db9f8a8</anchor>
      <arglist>(QGraphicsItem *parent=0)</arglist>
    </member>
    <member kind="function">
      <type>QRectF</type>
      <name>boundingRect</name>
      <anchorfile>classLoop.html</anchorfile>
      <anchor>85fd697e6615fc9ae83d1e6c970121aa</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QPainterPath</type>
      <name>shape</name>
      <anchorfile>classLoop.html</anchorfile>
      <anchor>ba4477ba6806b9a945eaf8b72fc19d2e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setSelected</name>
      <anchorfile>classLoop.html</anchorfile>
      <anchor>d705668c42c6b822608aa1bdf8048967</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>paint</name>
      <anchorfile>classLoop.html</anchorfile>
      <anchor>dbd64dc3130e9aabe92ca3e85afcc510</anchor>
      <arglist>(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addPath</name>
      <anchorfile>classLoop.html</anchorfile>
      <anchor>7d666211787c2bb756d9909f82cf117b</anchor>
      <arglist>(QPainterPath pathToAdd)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addTextPath</name>
      <anchorfile>classLoop.html</anchorfile>
      <anchor>43c75243f14565870fd83e4a0cc73fe1</anchor>
      <arglist>(QPainterPath pathToAdd)</arglist>
    </member>
    <member kind="function">
      <type>QVariant</type>
      <name>itemChange</name>
      <anchorfile>classLoop.html</anchorfile>
      <anchor>ee22beae5a87f3ecd18bf4a9552249cc</anchor>
      <arglist>(GraphicsItemChange change, const QVariant &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setReady</name>
      <anchorfile>classLoop.html</anchorfile>
      <anchor>508b764b772a818ab5b59a41d519c700</anchor>
      <arglist>(bool b)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setStart</name>
      <anchorfile>classLoop.html</anchorfile>
      <anchor>41c593acd96723f1c4da5e845649318e</anchor>
      <arglist>(QPointFWithParent sP)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setEnd</name>
      <anchorfile>classLoop.html</anchorfile>
      <anchor>38b57b4511be48550822cbd9afdf9e3d</anchor>
      <arglist>(QPointFWithParent eP)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setIsOutline</name>
      <anchorfile>classLoop.html</anchorfile>
      <anchor>2603a5aabb4d2ff31f40cdb514eff161</anchor>
      <arglist>(bool s)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setNumber</name>
      <anchorfile>classLoop.html</anchorfile>
      <anchor>896f7af2e011c433a7791845fe958f52</anchor>
      <arglist>(int nbr)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setTypeCircle</name>
      <anchorfile>classLoop.html</anchorfile>
      <anchor>e5f4994e7e0cf2ec813fc9d6af8a65b5</anchor>
      <arglist>(bool type)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setLeadIn</name>
      <anchorfile>classLoop.html</anchorfile>
      <anchor>9455d74a56a69b3ce6bdc5ce7662545e</anchor>
      <arglist>(QPointFWithParent p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setTouchPoint</name>
      <anchorfile>classLoop.html</anchorfile>
      <anchor>e4197bb0bc93783b5d3c6f6fc8598247</anchor>
      <arglist>(QPointFWithParent p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setEntities</name>
      <anchorfile>classLoop.html</anchorfile>
      <anchor>5df9e03d2641b9e72c73e7e104e76245</anchor>
      <arglist>(QPFWPVector ts)</arglist>
    </member>
    <member kind="function">
      <type>QPFWPVector</type>
      <name>getEntities</name>
      <anchorfile>classLoop.html</anchorfile>
      <anchor>a002f8baf39df036b0ed2a782d338126</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>QRectF</type>
      <name>qtRect</name>
      <anchorfile>classLoop.html</anchorfile>
      <anchor>57a162878b22637a4b2e4e2b658e4181</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QPainterPath</type>
      <name>loopShape</name>
      <anchorfile>classLoop.html</anchorfile>
      <anchor>f0e08f9ef47273fd9bde9e3539436d68</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QPainterPath</type>
      <name>originalShape</name>
      <anchorfile>classLoop.html</anchorfile>
      <anchor>161dce99f36f5dcd9d7e3fce5e2d9090</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QSettings</type>
      <name>settings</name>
      <anchorfile>classLoop.html</anchorfile>
      <anchor>91cf0487275db046ad781fd83f47d209</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QPen</type>
      <name>myPen</name>
      <anchorfile>classLoop.html</anchorfile>
      <anchor>a3736c0664ae99877041f726ab3c35e8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QPen</type>
      <name>selectedPen</name>
      <anchorfile>classLoop.html</anchorfile>
      <anchor>346872b27bc56f3afb5be28b315ee870</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QPen</type>
      <name>unSelectedPen</name>
      <anchorfile>classLoop.html</anchorfile>
      <anchor>de9eed40d7d525d343c16f78e674ee4d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QPen</type>
      <name>outlinePen</name>
      <anchorfile>classLoop.html</anchorfile>
      <anchor>0b374393f674693ef2a8bfe1ae8b7a17</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>showText</name>
      <anchorfile>classLoop.html</anchorfile>
      <anchor>b5b06148015aa01279edbc58a5560a49</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>loopNumber</name>
      <anchorfile>classLoop.html</anchorfile>
      <anchor>5e6489c52183919b43c9e058bd5d688f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>isCircle</name>
      <anchorfile>classLoop.html</anchorfile>
      <anchor>242a876ff09e813d783892aaa1d9bacf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>isOutline</name>
      <anchorfile>classLoop.html</anchorfile>
      <anchor>5523cfb2c8be1b2c15a5b1fecc201094</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>ready</name>
      <anchorfile>classLoop.html</anchorfile>
      <anchor>37c6f5cf76da4375fb235b7f7043050c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QPointFWithParent</type>
      <name>leadIn</name>
      <anchorfile>classLoop.html</anchorfile>
      <anchor>ec4f67b5a0a746ea612b5da5b52ccb85</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QPointFWithParent</type>
      <name>leadOut</name>
      <anchorfile>classLoop.html</anchorfile>
      <anchor>758fd13ec4c5b002e7efd09e645801ee</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QPointFWithParent</type>
      <name>startPoint</name>
      <anchorfile>classLoop.html</anchorfile>
      <anchor>bb8f4c98194e79b4c8d04834f3b32d63</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QPointFWithParent</type>
      <name>endPoint</name>
      <anchorfile>classLoop.html</anchorfile>
      <anchor>937946a7ec96ef24412a7dd02b543294</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QPointFWithParent</type>
      <name>touchPoint</name>
      <anchorfile>classLoop.html</anchorfile>
      <anchor>eccefff7a44afadcaf74ce6c635f4a6d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QPFWPVector</type>
      <name>entities</name>
      <anchorfile>classLoop.html</anchorfile>
      <anchor>e7586ec5b3e6cc42392cbdf7b6d32308</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>mouseDoubleClickEvent</name>
      <anchorfile>classLoop.html</anchorfile>
      <anchor>7f6e668292d755837e60e82cc43f5369</anchor>
      <arglist>(QGraphicsSceneMouseEvent *event)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MainWindow</name>
    <filename>classMainWindow.html</filename>
    <member kind="slot">
      <type>void</type>
      <name>openFile</name>
      <anchorfile>classMainWindow.html</anchorfile>
      <anchor>288b768c3c21a9171bdc56fe845ece8b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>nextPoint</name>
      <anchorfile>classMainWindow.html</anchorfile>
      <anchor>7cbd8c8b0d682e5a8b8d89c6d2ed1ee0</anchor>
      <arglist>(int currentLoop)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>MainWindow</name>
      <anchorfile>classMainWindow.html</anchorfile>
      <anchor>34c4b4207b46d11a4100c9b19f0e81bb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>createStatusBar</name>
      <anchorfile>classMainWindow.html</anchorfile>
      <anchor>f0a8a3f54a87bd7ad6f23248dd0e9c09</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>createToolBars</name>
      <anchorfile>classMainWindow.html</anchorfile>
      <anchor>cce4e32b95d3d5cb48470c053a1740c2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>createMenus</name>
      <anchorfile>classMainWindow.html</anchorfile>
      <anchor>a4907b0251d305659e403c62921ef331</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>createDockWindows</name>
      <anchorfile>classMainWindow.html</anchorfile>
      <anchor>5eabeda2fa3d2e1e2ddda56cb3511663</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>createActions</name>
      <anchorfile>classMainWindow.html</anchorfile>
      <anchor>62cd8712fb41a754298f6f60eead2cb0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>createConnections</name>
      <anchorfile>classMainWindow.html</anchorfile>
      <anchor>f773488e0b16efe6c0fc67ad348b86b2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>readSettings</name>
      <anchorfile>classMainWindow.html</anchorfile>
      <anchor>06476208b8466211f3bb0fcae787052b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>writeSettings</name>
      <anchorfile>classMainWindow.html</anchorfile>
      <anchor>49be45fc9b993fdc3afe55d4b6fa0650</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>openPart</name>
      <anchorfile>classMainWindow.html</anchorfile>
      <anchor>caa87e8b58102f5fe653450b13363885</anchor>
      <arglist>(QString file)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>trigActions</name>
      <anchorfile>classMainWindow.html</anchorfile>
      <anchor>0e38f41ffa2a177d182687e8c212d625</anchor>
      <arglist>(bool status)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>nameObjects</name>
      <anchorfile>classMainWindow.html</anchorfile>
      <anchor>34bc76bc28029c30f21e483f12386a67</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>createSheets</name>
      <anchorfile>classMainWindow.html</anchorfile>
      <anchor>65fcfa8a9b6bf49e492a47012036db6b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>QGraphicsView *</type>
      <name>previewSheet</name>
      <anchorfile>classMainWindow.html</anchorfile>
      <anchor>badc711d931319cee1d6718e893d641d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QGraphicsView *</type>
      <name>sheet</name>
      <anchorfile>classMainWindow.html</anchorfile>
      <anchor>308c1a516014fd0117b32d19968b3f9d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Sheet *</type>
      <name>scene</name>
      <anchorfile>classMainWindow.html</anchorfile>
      <anchor>f718c62ffdd88c1766642aa6e60c4e5d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Sheet *</type>
      <name>previewScene</name>
      <anchorfile>classMainWindow.html</anchorfile>
      <anchor>2ed94ec08aa8185e1910320c172453cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QDockWidget *</type>
      <name>previewDock</name>
      <anchorfile>classMainWindow.html</anchorfile>
      <anchor>f1121fa5dbc00578854c451ae15f5bf1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QDockWidget *</type>
      <name>dockInsertedParts</name>
      <anchorfile>classMainWindow.html</anchorfile>
      <anchor>8fbf6c69b0b404b0d3abf3451f91b437</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QDockWidget *</type>
      <name>filesListDock</name>
      <anchorfile>classMainWindow.html</anchorfile>
      <anchor>25900c17cdb1a3a586b3b9cf4e775588</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QPen</type>
      <name>contourPen</name>
      <anchorfile>classMainWindow.html</anchorfile>
      <anchor>9229819423e2e131db6080054e9d32b6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QBrush</type>
      <name>contourBrush</name>
      <anchorfile>classMainWindow.html</anchorfile>
      <anchor>291040ac8a5c2af85b8e3b0b318ed52e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QPalette</type>
      <name>successText</name>
      <anchorfile>classMainWindow.html</anchorfile>
      <anchor>df854594454ce3e813c0531f15f06608</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QPalette</type>
      <name>infoText</name>
      <anchorfile>classMainWindow.html</anchorfile>
      <anchor>1aa52aefeb5d3dd7b5d187c4b06b6e4c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QPalette</type>
      <name>errorText</name>
      <anchorfile>classMainWindow.html</anchorfile>
      <anchor>7953395ea2e2e00144b2f526c36422d8</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>closeEvent</name>
      <anchorfile>classMainWindow.html</anchorfile>
      <anchor>4e20a4a065fbb0e4d3532a45a0a91425</anchor>
      <arglist>(QCloseEvent *event)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Part</name>
    <filename>classPart.html</filename>
    <member kind="function">
      <type></type>
      <name>Part</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>13c14daa61068c3da9f2dba37a54fefd</anchor>
      <arglist>(const QPainterPath shape, QPFWPVector pointsList, QPPVector partPathsList, QPFWPVector circlePointsList, QPPVector circlesPathsList)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Part</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>81c949e170c877c2ef4916047274fd91</anchor>
      <arglist>(const Part &amp;parentPart)</arglist>
    </member>
    <member kind="function">
      <type>QRectF</type>
      <name>boundingRect</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>ce4103c8b6b558481eee19205ecbe9e4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QPainterPath</type>
      <name>shape</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>ba2b3bfdbe2d2c2227e474a8074f3269</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>paint</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>269d9d995fe8553b9b35838fd8d2304d</anchor>
      <arglist>(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)</arglist>
    </member>
    <member kind="function">
      <type>Part *</type>
      <name>copy</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>078dcfb9c3480d3e5768b755fbb74a01</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>start</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>7329b4251fde720574dddb89f79d9140</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>createOutlineLead</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>b0478a9fcec4d165ace12622a0668a05</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>generateLeads</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>cafed33ba74abad36176f6faf64f2161</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>findOutline</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>7aa55c76049d033b9347994cfb34f6ad</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>filterCircles</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>c8cd3a1d79a5982b7225463b929b6ea8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>generateLoops</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>20f2edb216d0b80e20768c464984de29</anchor>
      <arglist>(QPFWPVector ptsVector)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>shrink</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>70edcc0ef7e32cb1a5a9f559abd6a802</anchor>
      <arglist>(QPFWPVector &amp;pointsList, QPFWPVector &amp;pointsListNew, int &amp;pos, int &amp;oldPos)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>newPos</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>7ed3dc3bf279bd8efc7bdc6b658f716a</anchor>
      <arglist>(QPFWPVector &amp;pointsList)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>drawArc</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>2271b5c35f909ffeffb266de1bb45d8a</anchor>
      <arglist>(QPointFWithParent point, QPainterPath &amp;pathToModify)</arglist>
    </member>
    <member kind="function">
      <type>QPointFWithParent</type>
      <name>translateEntity</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>25d6378ef8474a6ab602cf5d8fc3a283</anchor>
      <arglist>(QPointFWithParent oldPoint, QPointF offset)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>optimizeRoute</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>0f18035b7ef71b6e9a7b60f6ff1ca05b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>moveMeBy</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>1555b923c4b55707cbfd03ed780c18e7</anchor>
      <arglist>(qreal dx, qreal dy)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setPartName</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>b8f8bca9e3cdfe782398567d65fef216</anchor>
      <arglist>(QString f)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>type</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>c52c40e35838d8f81d1929f76750f36b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>setMovePartVal</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>6688b95970845941f29a2814cb187fb0</anchor>
      <arglist>(double val)</arglist>
    </member>
    <member kind="variable">
      <type>QPainterPath</type>
      <name>partShape</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>569abd6d66b028f16f6b33455c71828c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QRectF</type>
      <name>qtRect</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>b1ff7fa084f4224abbea4044fcab33b4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QSettings</type>
      <name>settings</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>c8ac2568fe935d9c875a4cebfd61073d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>leadAngle</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>78c9ebff4a84acff555775a8f2b52299</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>leadDist</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>ce9e70c3cfd2bb0096308a7a400413d8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>preview</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>83774bea6e4ee0eeec4b38e16ea68530</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>nbrClosedPath</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>06c6fc808a494453e4a044d375232c2f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>nbrCircles</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>4706d2313a70b718a41eaa7a18636ada</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>outlinePos</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>51c73275a88ccceb13b903f72834213e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QVector&lt; Loop * &gt;</type>
      <name>partLoops</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>58c0b30feccd016419cde320fd018c57</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QVector&lt; Loop * &gt;</type>
      <name>partLoopsOpt</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>69aa7cd2ca376d38637ffec80eb63c2b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QPFWPVector</type>
      <name>ptsVector</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>57a6d508692af48734488603a01478d2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QPPVector</type>
      <name>pathsList</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>a31da9ad3a4293ff91f5f2d179ac130f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QPFWPVector</type>
      <name>cirPtsList</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>d1896fed157ee45917191dd24aa0b957</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QPPVector</type>
      <name>cirPathsList</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>f60a8902972f656b9acf3b05426213e3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QString</type>
      <name>partName</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>1efa34c174060e505f2ddacc544fbb0c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QPointFWithParent</type>
      <name>outlinePoint</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>eb11e856e82ba8997c30478a0fa902e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QPainterPath</type>
      <name>outLinePath</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>31330f0a8f6c53aec727c4a99badc56f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QPFWPVector</type>
      <name>gLeadPoints</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>1510dd645026193fa5ef0732491e8085</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QList&lt; QPFWPVector &gt;</type>
      <name>gLoops</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>e3f34c93f6c504fe29520649f49ad979</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QTransform</type>
      <name>transform</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>1b9587e9a48358df1a93b9a22ac8e819</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static double</type>
      <name>movePartVal</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>05b5ea1077b5b969fbb1891cbc33ce16</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>QVariant</type>
      <name>itemChange</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>29ffd48e67a955d1b265de247094304e</anchor>
      <arglist>(GraphicsItemChange change, const QVariant &amp;value)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>mousePressEvent</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>a89af738ac50fb73c3c2f26970e1ad00</anchor>
      <arglist>(QGraphicsSceneMouseEvent *event)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>mouseReleaseEvent</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>9cdd95eb9573dddea84c7819e8603974</anchor>
      <arglist>(QGraphicsSceneMouseEvent *event)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>mouseMoveEvent</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>b079db26ed80682e3611ce485de9556b</anchor>
      <arglist>(QGraphicsSceneMouseEvent *event)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>keyPressEvent</name>
      <anchorfile>classPart.html</anchorfile>
      <anchor>5cb524bfa63f28d8f1d35e45385af5c4</anchor>
      <arglist>(QKeyEvent *keyEvent)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Popu</name>
    <filename>classPopu.html</filename>
    <member kind="function">
      <type></type>
      <name>Popu</name>
      <anchorfile>classPopu.html</anchorfile>
      <anchor>9bb115faaffda6de9f95448af82c4e7a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>computeTotalRoute</name>
      <anchorfile>classPopu.html</anchorfile>
      <anchor>8540f87c3f77e194cc99901504bd1e9d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>sortContent</name>
      <anchorfile>classPopu.html</anchorfile>
      <anchor>a06d6c873d7c8e4dbaeae8ef77207e5b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>createNewGen</name>
      <anchorfile>classPopu.html</anchorfile>
      <anchor>837890a4cfbecef67e8cfa9c7fb4b683</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QPFWPVector</type>
      <name>init</name>
      <anchorfile>classPopu.html</anchorfile>
      <anchor>4d11b5d23818878c6a98b343ab7242e9</anchor>
      <arglist>(QPFWPVector points)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>selectParents</name>
      <anchorfile>classPopu.html</anchorfile>
      <anchor>0f7b2bc9be65a3a285ff75f4527486f9</anchor>
      <arglist>(Chromosome *parent1, Chromosome *parent2, int posd)</arglist>
    </member>
    <member kind="function">
      <type>Chromosome</type>
      <name>cross</name>
      <anchorfile>classPopu.html</anchorfile>
      <anchor>302de79186c83e2c4cfb6d8f0b13f445</anchor>
      <arglist>(Chromosome parent1, Chromosome parent2)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>selectTwoParents</name>
      <anchorfile>classPopu.html</anchorfile>
      <anchor>ac48e4e015c7564bbc2559da48a67fb8</anchor>
      <arglist>(Chromosome *p1, Chromosome *p2, int posd)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mutateImprove</name>
      <anchorfile>classPopu.html</anchorfile>
      <anchor>f3974f55b95a10e16065dadef46e7e58</anchor>
      <arglist>(int pos)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mutateImproveMe</name>
      <anchorfile>classPopu.html</anchorfile>
      <anchor>f05ba00d22d260eacef15d949059d418</anchor>
      <arglist>(int pos)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mutate</name>
      <anchorfile>classPopu.html</anchorfile>
      <anchor>80e85aeab121d93452d5ed3e8ae9754c</anchor>
      <arglist>(int i)</arglist>
    </member>
    <member kind="variable">
      <type>QVector&lt; Chromosome &gt;</type>
      <name>newGen</name>
      <anchorfile>classPopu.html</anchorfile>
      <anchor>91d5728ab826659fd6b8e71ab3ffd689</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>totalRoute</name>
      <anchorfile>classPopu.html</anchorfile>
      <anchor>8a40aa45e0b2a04033c519b4ffe8c485</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>popSize</name>
      <anchorfile>classPopu.html</anchorfile>
      <anchor>3560c074fce59b22cb4776d94f5f8707</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>Max_iter</name>
      <anchorfile>classPopu.html</anchorfile>
      <anchor>99471e314381011e9f9c756ab26e30ab</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>chromoSize</name>
      <anchorfile>classPopu.html</anchorfile>
      <anchor>3f6bf79b7262c24b76dbdd3d8706aaa5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QVector&lt; Chromosome &gt;</type>
      <name>content</name>
      <anchorfile>classPopu.html</anchorfile>
      <anchor>b87f03acbe585b7f045dff4c07ed63f8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QDumper</name>
    <filename>classQDumper.html</filename>
  </compound>
  <compound kind="class">
    <name>Sheet</name>
    <filename>classSheet.html</filename>
    <member kind="slot">
      <type>void</type>
      <name>cleanUpAnim</name>
      <anchorfile>classSheet.html</anchorfile>
      <anchor>49277fdafd35e09c2ff6493395c97ca4</anchor>
      <arglist>(bool end=false)</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>zoomFit</name>
      <anchorfile>classSheet.html</anchorfile>
      <anchor>f814897028f6e30c56d50abb83154bb6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>zoom</name>
      <anchorfile>classSheet.html</anchorfile>
      <anchor>0416139d5e22c1f9e5c22a9bc6b7f027</anchor>
      <arglist>(bool in=true)</arglist>
    </member>
    <member kind="signal">
      <type>void</type>
      <name>progressionDone</name>
      <anchorfile>classSheet.html</anchorfile>
      <anchor>68ca0ad362091abbad11b98b36fc3a27</anchor>
      <arglist>(const int currentLoop)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Sheet</name>
      <anchorfile>classSheet.html</anchorfile>
      <anchor>159e3ceed13658faa02789e556214210</anchor>
      <arglist>(bool preview=true, QWidget *parent=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setSheetRect</name>
      <anchorfile>classSheet.html</anchorfile>
      <anchor>0dc8870458359b049b50cb67a61d556d</anchor>
      <arglist>(QRect rect=QRect(0, 0, 1, 1))</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>moveTool</name>
      <anchorfile>classSheet.html</anchorfile>
      <anchor>279e6532ff30d78dab40d366cf9e8f4c</anchor>
      <arglist>(QPointF endPoint)</arglist>
    </member>
    <member kind="variable">
      <type>QBasicTimer</type>
      <name>timer</name>
      <anchorfile>classSheet.html</anchorfile>
      <anchor>3b142af96cbf0a47ca8624394d62e9cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QPen</type>
      <name>toolPen</name>
      <anchorfile>classSheet.html</anchorfile>
      <anchor>f81e9096401e6c2870235d51353ee5b9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QGraphicsRectItem *</type>
      <name>sheetRect</name>
      <anchorfile>classSheet.html</anchorfile>
      <anchor>42cdc726ac0bdc8c99ddd171483e0c08</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>mousePressEvent</name>
      <anchorfile>classSheet.html</anchorfile>
      <anchor>bde1c556fc3ee1de8f3355d557c0b1e1</anchor>
      <arglist>(QGraphicsSceneMouseEvent *mouseEvent)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>mouseMoveEvent</name>
      <anchorfile>classSheet.html</anchorfile>
      <anchor>420090e00bd072467fff36d8faf387b9</anchor>
      <arglist>(QGraphicsSceneMouseEvent *mouseEvent)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>mouseReleaseEvent</name>
      <anchorfile>classSheet.html</anchorfile>
      <anchor>b927c5f72d8003756e0112f406a2bfb7</anchor>
      <arglist>(QGraphicsSceneMouseEvent *mouseEvent)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>wheelEvent</name>
      <anchorfile>classSheet.html</anchorfile>
      <anchor>7216e30842cc96181d6aa347e3c71db1</anchor>
      <arglist>(QGraphicsSceneWheelEvent *mouseEvent)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>timerEvent</name>
      <anchorfile>classSheet.html</anchorfile>
      <anchor>fbf5b838ff9d124fc01ac90fd4658f2b</anchor>
      <arglist>(QTimerEvent *event)</arglist>
    </member>
  </compound>
</tagfile>
