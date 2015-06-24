<GameProjectFile>
  <PropertyGroup Type="Scene" Name="StageOneScene" ID="a2ee0952-26b5-49ae-8bf9-4f1d6279b798" Version="2.3.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="0" Speed="1.0000" />
      <ObjectData Name="StageOneScene" ctype="GameNodeObjectData">
        <Size X="1280.0000" Y="720.0000" />
        <Children>
          <AbstractNodeData Name="tileMap" ActionTag="2028102553" Tag="11" IconVisible="False" TopMargin="-48.0000" ctype="GameMapObjectData">
            <Size X="1280.0000" Y="768.0000" />
            <AnchorPoint />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize />
            <FileData Type="Normal" Path="rodrigo_big/cena_1.tmx" Plist="" />
          </AbstractNodeData>
          <AbstractNodeData Name="starButton" ActionTag="1983573685" Tag="21" IconVisible="False" LeftMargin="95.6082" RightMargin="1056.3918" TopMargin="67.2565" BottomMargin="524.7435" TouchEnable="True" FontSize="14" LeftEage="10" RightEage="10" TopEage="10" BottomEage="10" Scale9OriginX="10" Scale9OriginY="10" Scale9Width="12" Scale9Height="12" OutlineSize="0" ShadowOffsetX="0" ShadowOffsetY="0" ctype="ButtonObjectData">
            <Size X="128.0000" Y="128.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="159.6082" Y="588.7435" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.1247" Y="0.8177" />
            <PreSize X="0.1000" Y="0.1778" />
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
            <PressedFileData Type="Normal" Path="images/starOn.png" Plist="" />
            <NormalFileData Type="Normal" Path="images/star.png" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="255" G="127" B="80" />
          </AbstractNodeData>
          <AbstractNodeData Name="listing" ActionTag="1159327246" Tag="37" IconVisible="False" LeftMargin="697.6368" RightMargin="6.3633" TopMargin="36.2209" BottomMargin="431.7791" TouchEnable="True" ClipAble="True" BackColorAlpha="209" ComboBoxIndex="2" ColorAngle="90.0000" IsBounceEnabled="True" ScrollDirectionType="0" ItemMargin="2" DirectionType="Vertical" ctype="ListViewObjectData">
            <Size X="576.0000" Y="252.0000" />
            <AnchorPoint />
            <Position X="697.6368" Y="431.7791" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5450" Y="0.5997" />
            <PreSize X="0.4500" Y="0.3500" />
            <SingleColor A="255" R="150" G="150" B="255" />
            <FirstColor A="255" R="150" G="150" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="score" ActionTag="1596763673" Tag="52" VisibleForFrame="False" IconVisible="False" LeftMargin="832.8578" RightMargin="235.1422" TopMargin="382.4590" BottomMargin="282.5410" FontSize="48" LabelText="Score is : " OutlineSize="0" ShadowOffsetX="0" ShadowOffsetY="0" ctype="TextObjectData">
            <Size X="212.0000" Y="55.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="938.8578" Y="310.0410" />
            <Scale ScaleX="5.7378" ScaleY="12.5140" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.7335" Y="0.4306" />
            <PreSize />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="255" G="127" B="80" />
          </AbstractNodeData>
          <AbstractNodeData Name="coinHud" ActionTag="-2141821531" Tag="14" IconVisible="False" LeftMargin="11.3148" RightMargin="1236.6852" TopMargin="93.4808" BottomMargin="594.5192" ctype="SpriteObjectData">
            <Size X="32.0000" Y="32.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="27.3148" Y="610.5192" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.0213" Y="0.8479" />
            <PreSize />
            <FileData Type="Normal" Path="images/coinHud.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="lifeHud" ActionTag="267621548" Tag="15" IconVisible="False" LeftMargin="11.3148" RightMargin="1236.6852" TopMargin="42.2710" BottomMargin="645.7290" ctype="SpriteObjectData">
            <Size X="32.0000" Y="32.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="27.3148" Y="661.7290" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.0213" Y="0.9191" />
            <PreSize />
            <FileData Type="Normal" Path="images/lifeHud.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameProjectFile>