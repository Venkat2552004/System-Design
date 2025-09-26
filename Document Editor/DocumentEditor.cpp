#include <bits/stdc++.h>
using namespace std;

class DocumentElement {
public:
    virtual string render() = 0;
};

class TextElement : public DocumentElement {
private:
    string text;
public:
    TextElement(string text) {
        this->text = text;
    }
    string render() override{
        return text;
    }
};

class NewLineElement : public DocumentElement {
public:
    string render() override{
        return "\n";
    }
};

class TabSpaceElement : public DocumentElement {
public:
    string render() override{
        return "\t";
    }
};

class ImageElement : public DocumentElement {
private:
    string path;
public:
    ImageElement(string path) {
        this->path = path;
    }
    string render() override{
        return "Image path: [" + path + " ]";
    }
};


class Persistence {
public:
    virtual void save(string content) noexcept(false) = 0;
};

class FileStorage : public Persistence {
public:
    void save(string content) noexcept(false) override {
        // file save logic;
        try {
            ofstream out("document.txt");
            try {
                cout << "Saving in document.txt...\n";
                out << content;
                cout << "Successfully saved in document.txt\n";
            }
            catch(runtime_error error) {
                throw error;
            }
        }
        catch(runtime_error error) {
            cout << "Error: " << error.what() << endl;
        }
    }
};

class DbStorage : public Persistence {
public:
    void save(string content) override {
        // DB save logic;
        cout << "Savingg in Database...\n";
        cout << "Successfully saved in Database\n";
    }
};


class Document {
private:
    vector<DocumentElement*> elements;
public:
    void addElement(DocumentElement* element) {
        elements.push_back(element);
    }

    vector<DocumentElement*> getElements() {
        return elements;
    }
};


class DocumentEditor {
private:
    Document* document;
public:
    DocumentEditor(Document* document) {
        this->document = (document ? document : new Document());
    }

    void add(DocumentElement* element) {
        document->addElement(element);
    }

    Document* getDocument() {
        return document;
    }
};


class DocumentRenderer {
private:
    Document* document;
    string renderedContent;
public:
    DocumentRenderer(Document* document) {
        this->document = document;
    }

    string render() {
        if(renderedContent.empty()) {
            for(DocumentElement* element : document->getElements()) {
                renderedContent += element->render();
            }
        }
        return renderedContent;
    }
};


int main() {

    Persistence* fileStorage = new FileStorage();
    Persistence* dbStorage = new DbStorage();

    DocumentEditor* documentEditor = new DocumentEditor(nullptr);
    DocumentRenderer* documentRenderer = new DocumentRenderer(documentEditor->getDocument());

    documentEditor->add(new TextElement("Hii, this is Mahesh"));
    documentEditor->add(new NewLineElement());
    documentEditor->add(new TabSpaceElement());
    documentEditor->add(new TextElement("Currently learning and implementing System Design Concepts"));
    documentEditor->add(new NewLineElement());
    documentEditor->add(new ImageElement("image.jpg"));

    string content =  documentRenderer->render();

    fileStorage->save(content);
    dbStorage->save(content);
    
    return 0;
}