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
          <AbstractNodeData Name="hero" ActionTag="-1310216368" Tag="22" IconVisible="False" LeftMargin="295.2869" RightMargin="952.7131" TopMargin="367.6810" BottomMargin="320.3190" ctype="SpriteObjectData">
            <Size X="32.0000" Y="32.0000" />
            <Children>
              <AbstractNodeData Name="check" ActionTag="-1115354749" Tag="26" VisibleForFrame="False" IconVisible="False" LeftMargin="50.3440" RightMargin="-58.3440" TopMargin="-163.2818" BottomMargin="155.2818" TouchEnable="True" ctype="CheckBoxObjectData">
                <Size X="40.0000" Y="40.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="70.3440" Y="175.2818" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="2.1983" Y="5.4776" />
                <PreSize />
                <NormalBackFileData Type="Default" Path="Default/CheckBox_Normal.png" Plist="" />
                <PressedBackFileData Type="Default" Path="Default/CheckBox_Press.png" Plist="" />
                <DisableBackFileData Type="Default" Path="Default/CheckBox_Disable.png" Plist="" />
                <NodeNormalFileData Type="Default" Path="Default/CheckBoxNode_Normal.png" Plist="" />
                <NodeDisableFileData Type="Default" Path="Default/CheckBoxNode_Disable.png" Plist="" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="311.2869" Y="336.3190" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="0" B="0" />
            <PrePosition X="0.2432" Y="0.4671" />
            <PreSize />
            <FileData Type="Normal" Path="images/heroBlock.png" Plist="" />
            <BlendFunc Src="1" Dst="1" />
          </AbstractNodeData>
          <AbstractNodeData Name="listing" ActionTag="1159327246" Tag="37" IconVisible="False" PercentWidthEnable="True" PercentHeightEnable="True" PercentWidthEnabled="True" PercentHeightEnabled="True" LeftMargin="697.6368" RightMargin="6.3633" TopMargin="36.2209" BottomMargin="431.7791" TouchEnable="True" BackColorAlpha="102" ComboBoxIndex="1" ColorAngle="90.0000" ScrollDirectionType="0" DirectionType="Vertical" ctype="ListViewObjectData">
            <Size X="576.0000" Y="252.0000" />
            <Children>
              <AbstractNodeData Name="Text_2_0_0" ActionTag="1453374063" Tag="38" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" RightMargin="403.0000" BottomMargin="229.0000" FontSize="20" LabelText="-Personagem Pula?" OutlineSize="0" ShadowOffsetX="0" ShadowOffsetY="0" ctype="TextObjectData">
                <Size X="173.0000" Y="23.0000" />
                <Children>
                  <AbstractNodeData Name="CheckBox_1" ActionTag="164462600" Tag="39" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="173.0000" RightMargin="-24.0000" TopMargin="-0.5000" BottomMargin="-0.5000" TouchEnable="True" ctype="CheckBoxObjectData">
                    <Size X="24.0000" Y="24.0000" />
                    <AnchorPoint ScaleY="0.5000" />
                    <Position X="173.0000" Y="11.5000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="1.0000" Y="0.5000" />
                    <PreSize X="0.1387" Y="1.0435" />
                    <NormalBackFileData Type="Default" Path="Default/CheckBox_Normal.png" Plist="" />
                    <PressedBackFileData Type="Default" Path="Default/CheckBox_Press.png" Plist="" />
                    <DisableBackFileData Type="Default" Path="Default/CheckBox_Disable.png" Plist="" />
                    <NodeNormalFileData Type="Default" Path="Default/CheckBoxNode_Normal.png" Plist="" />
                    <NodeDisableFileData Type="Default" Path="Default/CheckBoxNode_Disable.png" Plist="" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleY="0.5000" />
                <Position Y="240.5000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="0" G="0" B="0" />
                <PrePosition Y="0.9544" />
                <PreSize X="0.3003" Y="0.0799" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="255" G="127" B="80" />
              </AbstractNodeData>
              <AbstractNodeData Name="Text_2_0_0_0" ActionTag="2119957518" ZOrder="1" Tag="42" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" RightMargin="346.0000" TopMargin="23.0000" BottomMargin="206.0000" FontSize="20" LabelText="-Personagem Movimenta?" OutlineSize="0" ShadowOffsetX="0" ShadowOffsetY="0" ctype="TextObjectData">
                <Size X="230.0000" Y="23.0000" />
                <Children>
                  <AbstractNodeData Name="CheckBox_0" ActionTag="758471182" Tag="43" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="230.0000" RightMargin="-24.0000" TopMargin="0.3966" BottomMargin="-1.3966" TouchEnable="True" ctype="CheckBoxObjectData">
                    <Size X="24.0000" Y="24.0000" />
                    <AnchorPoint ScaleY="0.5157" />
                    <Position X="230.0000" Y="10.9802" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="1.0000" Y="0.4774" />
                    <PreSize X="0.1043" Y="1.0435" />
                    <NormalBackFileData Type="Default" Path="Default/CheckBox_Normal.png" Plist="" />
                    <PressedBackFileData Type="Default" Path="Default/CheckBox_Press.png" Plist="" />
                    <DisableBackFileData Type="Default" Path="Default/CheckBox_Disable.png" Plist="" />
                    <NodeNormalFileData Type="Default" Path="Default/CheckBoxNode_Normal.png" Plist="" />
                    <NodeDisableFileData Type="Default" Path="Default/CheckBoxNode_Disable.png" Plist="" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleY="0.5000" />
                <Position Y="217.5000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="0" G="0" B="0" />
                <PrePosition Y="0.8631" />
                <PreSize X="0.3003" Y="0.0799" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="255" G="127" B="80" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleY="1.0000" />
            <Position X="697.6368" Y="683.7791" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5450" Y="0.9497" />
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
          <AbstractNodeData Name="coinHud" ActionTag="-2141821531" Tag="14" IconVisible="False" LeftMargin="28.7898" RightMargin="1219.2102" TopMargin="-24.1708" BottomMargin="712.1708" ctype="SpriteObjectData">
            <Size X="32.0000" Y="32.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="44.7898" Y="728.1708" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.0350" Y="1.0113" />
            <PreSize />
            <FileData Type="Normal" Path="images/coinHud.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="lifeHud" ActionTag="267621548" Tag="15" IconVisible="False" LeftMargin="28.7898" RightMargin="1219.2102" TopMargin="19.8085" BottomMargin="668.1915" ctype="SpriteObjectData">
            <Size X="32.0000" Y="32.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="44.7898" Y="684.1915" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.0350" Y="0.9503" />
            <PreSize />
            <FileData Type="Normal" Path="images/lifeHud.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameProjectFile>