<GameProjectFile>
  <PropertyGroup Type="Scene" Name="StageOneScene" ID="a2ee0952-26b5-49ae-8bf9-4f1d6279b798" Version="2.2.6.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="0" Speed="1.0000" />
      <ObjectData Name="StageOneScene" ctype="GameNodeObjectData">
        <Size X="1280.0000" Y="720.0000" />
        <Children>
          <AbstractNodeData Name="tileMap" ActionTag="2028102553" Tag="11" IconVisible="False" LeftMargin="8.8962" RightMargin="471.1038" TopMargin="-3.6241" BottomMargin="83.6241" ctype="GameMapObjectData">
            <Size X="800.0000" Y="640.0000" />
            <AnchorPoint />
            <Position X="8.8962" Y="83.6241" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.0070" Y="0.1161" />
            <PreSize />
            <FileData Type="Normal" Path="rodrigo/cena_1.tmx" Plist="" />
          </AbstractNodeData>
          <AbstractNodeData Name="starButton" ActionTag="1983573685" Tag="21" IconVisible="False" LeftMargin="97.1838" RightMargin="1054.8162" TopMargin="75.1241" BottomMargin="516.8759" TouchEnable="True" FontSize="14" LeftEage="10" RightEage="10" TopEage="10" BottomEage="10" Scale9OriginX="10" Scale9OriginY="10" Scale9Width="12" Scale9Height="12" OutlineSize="1" ShadowOffsetX="2" ShadowOffsetY="-2" ctype="ButtonObjectData">
            <Size X="128.0000" Y="128.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="161.1838" Y="580.8759" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.1259" Y="0.8068" />
            <PreSize X="0.1000" Y="0.1778" />
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
            <PressedFileData Type="Normal" Path="images/starOn.png" Plist="" />
            <NormalFileData Type="Normal" Path="images/star.png" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="255" G="127" B="80" />
          </AbstractNodeData>
          <AbstractNodeData Name="hero" ActionTag="-1310216368" Tag="22" IconVisible="False" LeftMargin="45.3630" RightMargin="1202.6370" TopMargin="378.4118" BottomMargin="309.5882" ctype="SpriteObjectData">
            <Size X="32.0000" Y="32.0000" />
            <Children>
              <AbstractNodeData Name="check" ActionTag="-1115354749" Tag="26" IconVisible="False" LeftMargin="84.4984" RightMargin="-92.4984" TopMargin="-135.6627" BottomMargin="127.6627" TouchEnable="True" ctype="CheckBoxObjectData">
                <Size X="40.0000" Y="40.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="104.4984" Y="147.6627" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="3.2656" Y="4.6145" />
                <PreSize />
                <NormalBackFileData Type="Default" Path="Default/CheckBox_Normal.png" Plist="" />
                <PressedBackFileData Type="Default" Path="Default/CheckBox_Press.png" Plist="" />
                <DisableBackFileData Type="Default" Path="Default/CheckBox_Disable.png" Plist="" />
                <NodeNormalFileData Type="Default" Path="Default/CheckBoxNode_Normal.png" Plist="" />
                <NodeDisableFileData Type="Default" Path="Default/CheckBoxNode_Disable.png" Plist="" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="61.3630" Y="325.5882" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="0" B="0" />
            <PrePosition X="0.0479" Y="0.4522" />
            <PreSize />
            <FileData Type="Normal" Path="images/heroBlock.png" Plist="" />
            <BlendFunc Src="1" Dst="1" />
          </AbstractNodeData>
          <AbstractNodeData Name="listing" ActionTag="1159327246" Tag="37" IconVisible="False" PercentWidthEnable="True" PercentHeightEnable="True" LeftMargin="700.4061" RightMargin="3.5939" TopMargin="7.3243" BottomMargin="424.6757" TouchEnable="True" BackColorAlpha="102" ComboBoxIndex="1" ColorAngle="90.0000" ScrollDirectionType="0" DirectionType="Vertical" VerticalType="0" ctype="ListViewObjectData">
            <Size X="576.0000" Y="288.0000" />
            <Children>
              <AbstractNodeData Name="Text_2_0_0" ActionTag="1453374063" Tag="38" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" RightMargin="403.0000" BottomMargin="265.0000" FontSize="20" LabelText="-Personagem Pula?" OutlineSize="1" ShadowOffsetX="2" ShadowOffsetY="-2" ctype="TextObjectData">
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
                <Position Y="276.5000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition Y="0.9601" />
                <PreSize X="0.3003" Y="0.0799" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="255" G="127" B="80" />
              </AbstractNodeData>
              <AbstractNodeData Name="Text_2_0_0_0" ActionTag="2119957518" ZOrder="1" Tag="42" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" RightMargin="346.0000" TopMargin="23.0000" BottomMargin="242.0000" FontSize="20" LabelText="-Personagem Movimenta?" OutlineSize="1" ShadowOffsetX="2" ShadowOffsetY="-2" ctype="TextObjectData">
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
                <Position Y="253.5000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition Y="0.8802" />
                <PreSize X="0.3003" Y="0.0799" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="255" G="127" B="80" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleY="1.0000" />
            <Position X="700.4061" Y="712.6757" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5472" Y="0.9898" />
            <PreSize X="0.4500" Y="0.4000" />
            <SingleColor A="255" R="150" G="150" B="255" />
            <FirstColor A="255" R="150" G="150" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="score" ActionTag="1596763673" Tag="52" VisibleForFrame="False" IconVisible="False" LeftMargin="832.8578" RightMargin="235.1422" TopMargin="382.4590" BottomMargin="282.5410" FontSize="48" LabelText="Score is : " OutlineSize="1" ShadowOffsetX="2" ShadowOffsetY="-2" ctype="TextObjectData">
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
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameProjectFile>