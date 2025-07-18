const vscode = require('vscode');

async function convertAllMarkdownToPDF() {
    console.log('Starting batch PDF conversion...');
    
    const workspaceFolder = vscode.workspace.workspaceFolders[0];
    if (!workspaceFolder) {
        vscode.window.showErrorMessage('No workspace folder found');
        return;
    }
    
    const files = await vscode.workspace.findFiles('**/*.md', null, 100);
    console.log(Found  markdown files);
    
    for (const file of files) {
        try {
            console.log(Converting: );
            const document = await vscode.workspace.openTextDocument(file);
            await vscode.window.showTextDocument(document);
            
            // Wait a moment for the document to load
            await new Promise(resolve => setTimeout(resolve, 500));
            
            // Execute the markdown-pdf export command
            await vscode.commands.executeCommand('markdown-pdf.pdf');
            
            // Wait for conversion to complete
            await new Promise(resolve => setTimeout(resolve, 2000));
            
            console.log(Converted: );
        } catch (error) {
            console.error(Error converting :, error);
        }
    }
    
    vscode.window.showInformationMessage('Batch PDF conversion completed!');
}

// Execute the function
convertAllMarkdownToPDF();
