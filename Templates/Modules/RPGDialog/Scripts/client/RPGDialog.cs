//-----------------------------------------------------------------------------
// RPGDialog - Presents the player with a question and several answers to select from
// Created by Nelson A. K. Gonsalves
//-----------------------------------------------------------------------------

if($RPGDialogEditorPref::MaxOptions>0)
   $Pref::RPGDialog::MaxOptions=$RPGDialogEditorPref::MaxOptions;
   
function getQuestion(%questionFile,%questionNumber)
{
   %file = new FileObject();
   if(isFile($Pref::RPGDialog::Client::QuestionPath@%questionFile@".dlq") && %file.openForRead($Pref::RPGDialog::Client::QuestionPath@%questionFile@".dlq"))
   {
      for(%i=1;%i<%questionNumber;%i++)
      {
         %file.readLine();
         if(%file.isEOF())
            return "<Invalid Question>";
      }
      %question=%file.readLine();
   }
   else  if(isFile($RPGDialogEditorPref::QuestionPath@%questionFile@".dlq") && %file.openForRead($RPGDialogEditorPref::QuestionPath@%questionFile@".dlq"))
   {
      for(%i=1;%i<%questionNumber;%i++)
      {
         %file.readLine();
         if(%file.isEOF())
            return "<Invalid Question>";
      }
      %question=%file.readLine();
   }
   %file.close();
   %file.delete();
   return %question;
}

function clientCmdCloseRPGDialog()
{
   Canvas.popDialog(RPGDialog);
   RPGDialogQuestion.settext("");
   RPGDialogAnswer.settext("");
}

function clientCmdRPGDialogMessage(%sender,%senderName,%portrait,%npcFile,%questionNumber,%playerName)
{
   $RPGDialog::Sender=%sender;
   $RPGDialog::questionNumber=%questionNumber;
   onRPGDialogMessage(%npcFile,%questionNumber,%senderName,%portrait,%playerName);
}

function onRPGDialogMessage(%npcFile,%questionNumber,%senderName,%portrait,%playerName)
{
    if(%portrait!$="" && isFile($RPGDialogEditorPref::PortraitsPath@%portrait))
    {
       RPGDialogPortrait.setbitmap($RPGDialogEditorPref::PortraitsPath@%portrait);
    }
    else
    {
       RPGDialogPortrait.setbitmap($RPGDialogEditorPref::PortraitsPath@"unknown.png");
    }
    
    if(%npcFile!$="")
    {
       %QuestionAnswer=GetQuestion(%npcfile,%questionNumber);
       
       if(%QuestionAnswer!$="<InvalidQuestion>")
       {
          %AnswerStart=strPos(%QuestionAnswer,"<AnswerStart>");
          %question=getSubStr(%QuestionAnswer,0,%AnswerStart);
          %answer=getSubStr(%QuestionAnswer,%AnswerStart+13,strLen(%QuestionAnswer));
       }
       else
       {
       %question="ERROR::Invalid Question!!\nnpcFile = "@%npcFile@"\nquestionNumber = "@%questionNumber;
       }
    }
    
    if (%question!$="")
    {
       %question=strreplace(%question,"<<Name>>",%senderName);
       %question=strreplace(%question,"<<PlayerName>>",%playerName);
       

       if ((%soundStart = playRPGDialogSound(%question)) != -1)
          %question = getSubStr(%question, 0, %soundStart);

       RPGDialogQuestion.settext(%question);
       ChatHud.addLine($Pref::RPGDialog::ChatHudQuestionColor@%senderName@": "@StripMLControlChars(%question));
    }

    if (%answer!$="")
    {
       %answer=strReplace(%answer,"<<Name>>",%senderName);
       %answer=strReplace(%answer,"<<PlayerName>>",%playerName);
       %answer=strReplace(%answer,"<BR>","\n");

       %line=%answer;
       %i=1;
       while(%i<=$Pref::RPGDialog::MaxOptions) //lets number the options
       {
          %Start=strpos(%line,"<a:RPGDialog "@%i@">");

          if(%Start<0)
          {
             %i=$Pref::RPGDialog::MaxOptions+1;
          }
          else
          {
             %line=getSubStr(%line,%Start,strlen(%line));
             %End=strpos(%line,"</a>")+4;
             %line=getSubStr(%line,%End,strlen(%line));
             %answer=strReplace(%answer,"<a:RPGDialog "@%i@">","<a:RPGDialog "@%i@"> "@%i@" - ");
             %i++;
          }
       }

       
       RPGDialogAnswer.settext(%answer);
    }
    else
    {
       RPGDialogAnswer.settext("<a:RPGDialogNoAnswer>Continue...");
    }
    RPGDialogAnswer.Visible=true;

    Canvas.pushDialog(RPGDialog);
}

function RPGDialogAnswer::onURL(%this, %url)
{
//same as RPGDialogQuestion::onURL, so just forward the call
RPGDialogQuestion::onURL(%this, %url);
}

function RPGDialogQuestion::onURL(%this, %url)
{
   if(firstword(%url)!$="RPGDialog" && firstword(%url)!$="RPGDialogLink" && firstword(%url)!$="RPGDialogNoAnswer")
   {
      gotoWebPage( %url );
   }
   else if(firstword(%url)$="RPGDialogLink")
   {
      %Answers=%this.gettext();
      %AnswerHeaderSize=strlen("<a:RPGDialogLink "@restwords(%url)@">");
      %AnswerStart=strpos(%Answers,"<a:RPGDialogLink "@restwords(%url)@">")+%AnswerHeaderSize;
      %Answers=getSubStr(%Answers,%AnswerStart,strLen(%Answers));
      %AnswerEnd=strPos(%Answers,"</a>")+4;

      ChatHud.addLine($Pref::RPGDialog::ChatHudAnswerColor@"You: "@StripMLControlChars(getSubStr(%Answers,0,%AnswerEnd)));

      CommandToServer('RPGDialogAnswer', $RPGDialog::Sender, $RPGDialog::questionNumber, "QL"@restwords(%url));

      Canvas.popDialog(RPGDialog);
      RPGDialogQuestion.settext("");
      RPGDialogAnswer.settext("");
   }
   else if(firstword(%url)$="RPGDialogNoAnswer")
   {
      Canvas.popDialog(RPGDialog);
      RPGDialogQuestion.settext("");
      RPGDialogAnswer.settext("");
   }
   else
   {
      %Answers=%this.gettext();
      %Answers=strReplace(%Answers,restwords(%url)@" - ","");
      %AnswerHeaderSize=strlen("<a:RPGDialog "@restwords(%url)@">");
      %AnswerStart=strpos(%Answers,"<a:RPGDialog "@restwords(%url)@">")+%AnswerHeaderSize;
      %Answers=getSubStr(%Answers,%AnswerStart,strLen(%Answers));
      %AnswerEnd=strpos(%Answers,"</a>")+4;

      ChatHud.addLine($Pref::RPGDialog::ChatHudAnswerColor@"You: "@StripMLControlChars(getSubStr(%Answers,0,%AnswerEnd)));
 
      CommandToServer('RPGDialogAnswer', $RPGDialog::Sender, $RPGDialog::questionNumber, restwords(%url));

      Canvas.popDialog(RPGDialog);
      RPGDialogQuestion.settext("");
      RPGDialogAnswer.settext("");
   }
}

function playRPGDialogSound(%message)
{
   // Search for wav tag marker.
   %soundStart = strstr(%message, "~Sound:");
   if (%soundStart == -1) {
      return -1;
   }

   if(alxIsPlaying($RPGDialogSoundHandle))
      alxStop($RPGDialogSoundHandle);

   %sound = getSubStr(%message, %soundStart + 7, strLen(%message));
   $RPGDialogSoundHandle = alxPlay(%sound);

   return %soundStart;
}

function SelectAnswer(%Number)
{
   if(strPos(RPGDialogAnswer.getText(),"<a:RPGDialog "@%Number@">")>=0)
      RPGDialogAnswer.onURL("RPGDialog "@%Number);
   else
      OutOfRPGDialogFunction(%Number);
}