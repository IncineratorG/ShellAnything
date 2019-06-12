/**********************************************************************************
 * MIT License
 * 
 * Copyright (c) 2018 Antoine Beauchamp
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *********************************************************************************/

#include "TestMenu.h"
#include "shellanything/Icon.h"
#include "shellanything/Menu.h"
#include "shellanything/ActionExecute.h"

namespace shellanything { namespace test
{
  Menu * newMenu(const std::string & name)
  {
    Menu * menu = new Menu();
    menu->setName(name);
    return menu;
  }

  class MyMenu : public Menu
  {
  public:
    MyMenu(bool * deleted_flag)
    {
      this->deleted_flag = deleted_flag;
      (*deleted_flag) = false;
    }
    virtual ~MyMenu()
    {
      (*deleted_flag) = true;
    }
  private:
    bool * deleted_flag;
  };

  class MyAction : public Action
  {
  public:
    MyAction(bool * deleted_flag, bool * executed_flag)
    {
      this->deleted_flag  = deleted_flag;
      this->executed_flag = executed_flag;
      (*deleted_flag)  = false;
      (*executed_flag) = false;
    }
    virtual ~MyAction()
    {
      (*deleted_flag) = true;
    }
    virtual bool execute(const Context & iContext) const
    {
      (*executed_flag) = true;
      return true;
    }
  private:
    bool * deleted_flag;
    bool * executed_flag;
  };

  class MyIcon : public Icon
  {
  public:
    MyIcon(bool * deleted_flag)
    {
      this->deleted_flag  = deleted_flag;
      (*deleted_flag)  = false;
    }
    virtual ~MyIcon()
    {
      (*deleted_flag) = true;
    }
  private:
    bool * deleted_flag;
  };


  //--------------------------------------------------------------------------------------------------
  void TestMenu::SetUp()
  {
  }
  //--------------------------------------------------------------------------------------------------
  void TestMenu::TearDown()
  {
  }
  //--------------------------------------------------------------------------------------------------
  TEST_F(TestMenu, testMenuOwnership)
  {
    Menu * root =   newMenu("html");
    Menu * body =   newMenu("body");
    Menu * child1 = newMenu("h1");
    Menu * child2 = newMenu("p");
    Menu * child3 = newMenu("p");

    //no children yet
    bool deleted = false;
    MyMenu * my_test_menu = new MyMenu(&deleted);
    ASSERT_FALSE( deleted );

    //build tree
    root->addChild(body);
    body->addChild(child1);
    body->addChild(child2);
    body->addChild(child3);
    child3->addChild(my_test_menu); //root takes ownership of my_test_menu

    //destroy the tree
    delete root;
    root = NULL;

    //assert that MyMenu destructor was run
    ASSERT_TRUE(deleted);
  }
  //--------------------------------------------------------------------------------------------------
  TEST_F(TestMenu, testActionOwnership)
  {
    Menu * root =   newMenu("html");
    Menu * body =   newMenu("body");
    Menu * child1 = newMenu("h1");
    Menu * child2 = newMenu("p");
    Menu * child3 = newMenu("p");

    //no children yet
    bool deleted = false;
    bool executed = false;
    MyAction * my_test_action = new MyAction(&deleted, &executed);
    ASSERT_FALSE( deleted );

    //build tree
    root->addChild(body);
    body->addChild(child1);
    body->addChild(child2);
    body->addChild(child3);
    child3->addAction(my_test_action); //child3 takes ownership of my_test_menu

    //destroy the tree
    delete root;
    root = NULL;

    //assert that MyAction destructor was run
    ASSERT_TRUE(deleted);
  }
  //--------------------------------------------------------------------------------------------------
  TEST_F(TestMenu, testSubMenus)
  {
    Menu * root =   newMenu("html");
    Menu * body =   newMenu("body");
    Menu * child1 = newMenu("h1");
    Menu * child2 = newMenu("p");
    Menu * child3 = newMenu("p");

    //no children yet
    ASSERT_TRUE( root->getSubMenus().empty() );

    //build tree
    root->addChild(body);
    body->addChild(child1);
    body->addChild(child2);
    body->addChild(child3);

    Menu::MenuPtrList subs = body->getSubMenus();
    ASSERT_EQ(3, subs.size());
    ASSERT_EQ( child1, subs[0] );
    ASSERT_EQ( child2, subs[1] );
    ASSERT_EQ( child3, subs[2] );

    //destroy the tree
    delete root;
    root = NULL;
  }
  //--------------------------------------------------------------------------------------------------
  TEST_F(TestMenu, testAssignCommandIds)
  {
    Menu * root =   newMenu("html");
    Menu * body =   newMenu("body");
    Menu * child1 = newMenu("h1");
    Menu * child2 = newMenu("p0");
    Menu * child3 = newMenu("p1");
    Menu * child4 = newMenu("p1.1");
    Menu * child5 = newMenu("p1.2");
    Menu * child6 = newMenu("p2");
 
    //build tree
    root->addChild(body);
    body->addChild(child1);
    body->addChild(child2);
    body->addChild(child3);
    child3->addChild(child4);
    child3->addChild(child5);
    body->addChild(child6);
 
    //act
    uint32_t nextAvailableId = root->assignCommandIds(101);
 
    //assert
    ASSERT_EQ(109, nextAvailableId);
    ASSERT_EQ(101,   root->getCommandId());
    ASSERT_EQ(102,   body->getCommandId());
    ASSERT_EQ(103, child1->getCommandId());
    ASSERT_EQ(104, child2->getCommandId());
    ASSERT_EQ(105, child3->getCommandId());
    ASSERT_EQ(106, child4->getCommandId());
    ASSERT_EQ(107, child5->getCommandId());
    ASSERT_EQ(108, child6->getCommandId());
 
    //destroy the tree
    delete root;
    root = NULL;
  }
  //--------------------------------------------------------------------------------------------------
  TEST_F(TestMenu, testFindMenuByCommandId)
  {
    Menu * root =   newMenu("html");
    Menu * body =   newMenu("body");
    Menu * child1 = newMenu("h1");
    Menu * child2 = newMenu("p0");
    Menu * child3 = newMenu("p1");
    Menu * child4 = newMenu("p1.1");
    Menu * child5 = newMenu("p1.2");
    Menu * child6 = newMenu("p2");
 
    //build tree
    root->addChild(body);
    body->addChild(child1);
    body->addChild(child2);
    body->addChild(child3);
    child3->addChild(child4);
    child3->addChild(child5);
    body->addChild(child6);
 
    //act
    uint32_t nextAvailableId = root->assignCommandIds(101);
 
    //assert
    ASSERT_EQ( (Menu*)NULL, root->findMenuByCommandId(9999999));
 
    ASSERT_EQ(  root, root->findMenuByCommandId(101));
    ASSERT_EQ(  body, root->findMenuByCommandId(102));
    ASSERT_EQ(child1, root->findMenuByCommandId(103));
    ASSERT_EQ(child2, root->findMenuByCommandId(104));
    ASSERT_EQ(child3, root->findMenuByCommandId(105));
    ASSERT_EQ(child4, root->findMenuByCommandId(106));
    ASSERT_EQ(child5, root->findMenuByCommandId(107));
    ASSERT_EQ(child6, root->findMenuByCommandId(108));
 
    //destroy the tree
    delete root;
    root = NULL;
  }
  //--------------------------------------------------------------------------------------------------

} //namespace test
} //namespace shellanything
